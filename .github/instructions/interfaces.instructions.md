---
name: 'ThunderInterfaces'
description: 'Rules for working in this repo — published COM-RPC interface headers and generated JSON-RPC wrappers'
applyTo: '**'
---

# ThunderInterfaces

This repo contains **published ABI** — the shared COM-RPC interfaces consumed by all Thunder plugins and the daemon. Every interface here is a contract across process boundaries. Mistakes here break binary compatibility for every downstream plugin and consumer.

## ABI Immutability Rule
**Once an interface is merged to main, its existing methods can NEVER be changed or removed.**
- Changing a method signature (parameter types, order, return type) breaks all compiled proxy/stub pairs.
- Removing a method leaves dangling stubs that crash OOP plugins.
- To evolve: **append** new methods at the end of the interface only.
- To replace: create a new interface (`IMyInterface2`) with a new ID, and mark the old one `DEPRECATED`.

## Interface File Structure (`interfaces/I*.h`)
Every interface follows this canonical pattern:
```cpp
// @json 1.0.0
struct EXTERNAL IMyInterface : virtual public Core::IUnknown {
    enum { ID = RPC::ID_MY_INTERFACE };

    // @brief Description of MyEvent
    // @param value: The value that changed
    struct INotification : virtual public Core::IUnknown {
        enum { ID = RPC::ID_MY_INTERFACE_NOTIFICATION };
        virtual void MyEvent(const uint32_t value) = 0;
    };

    virtual ~IMyInterface() = default;

    virtual Core::hresult Register(INotification* const sink) = 0;
    virtual Core::hresult Unregister(const INotification* const sink) = 0;

    // @property
    // @brief Gets or sets the current value
    virtual Core::hresult Value(uint32_t& value /* @out */) const = 0;
    virtual Core::hresult Value(const uint32_t value) = 0;

    virtual Core::hresult DoSomething(const string& input /* @in */, uint32_t& result /* @out */) = 0;
};
```

## Interface IDs — `interfaces/Ids.h`
- Every interface and iterator **must** have a unique numeric ID in `interfaces/Ids.h`.
- IDs are assigned in sequential blocks — find the next available value; never reuse a value.
- Convention: `RPC::ID_MY_INTERFACE`, `RPC::ID_MY_INTERFACE_NOTIFICATION`, `RPC::ID_MY_ITERATOR`.
- Core COM IDs (for `Thunder/Source/com/` internals) live in `Thunder/Source/com/Ids.h` — do not assign those here.

## Annotation Tags — Drive Code Generation
All tags go in **comments immediately above the declaration** they annotate:

| Tag | Where | Effect |
|-----|-------|--------|
| `// @json 1.0.0` | Interface struct | Generates JSON-RPC wrapper at this version |
| `// @json:omit` | Method | Exclude this method from JSON-RPC generation |
| `/* @stubgen:omit */` | Class or method | Skip proxy/stub generation entirely |
| `/* @stubgen:stub */` | Method | Emit an empty stub (in-process-only method) |
| `/* @in */` | Parameter | Input parameter (default for `const` params) |
| `/* @out */` | Parameter | Output parameter (default for `&` non-const params) |
| `/* @inout */` | Parameter | Both input and output |
| `// @restrict:N` | Parameter | Maximum element count (required for arrays) |
| `// @optional` | Parameter | Parameter may be omitted in JSON |
| `// @text:name` | Method/enum | Override the JSON name for this symbol |
| `// @brief desc` | Method/property | Documentation string in generated output |
| `// @param name: desc` | Method | Parameter documentation |
| `// @property` | Method pair | Generates as JSON-RPC property (getter/setter) |
| `// @statuslistener` | Interface | Generates notification register/unregister |
| `@insert <file>` | File top | Pull in another header for type resolution |

## Code Generation Workflow
After editing an interface header, regenerate the proxy/stub and JSON-RPC wrapper using the `ThunderTools` generators (installed into the local `install/` prefix during the ThunderTools build):

```bash
# Regenerate proxy/stub for a single interface:
install/bin/ProxyStubGenerator \
    --include interfaces/ \
    --output ProxyStubs/ \
    interfaces/IMyInterface.h

# Regenerate JSON-RPC wrapper:
install/bin/JsonGenerator \
    --include interfaces/ \
    --output jsonrpc/ \
    interfaces/IMyInterface.h
```

- **Generated files** live in `jsonrpc/` — **never hand-edit them**; always regenerate.
- Generated proxy/stub `.cpp` files live in `ProxyStubs/` — also auto-generated, do not hand-edit.
- After regeneration, rebuild ThunderInterfaces:
  ```bash
  cmake --build build/ThunderInterfaces --target install
  ```

## Return Types
- **All interface methods must return `Core::hresult`** (Thunder 5.0+).
- `Core::ERROR_NONE` (0) for success.
- Avoid `void` return — use `Core::hresult` even for infallible methods, to allow future error propagation.
- For properties: use a `const` getter overload (`Value(uint32_t& /* @out */) const`) and a setter overload (`Value(const uint32_t)`).

## Collections in Interfaces
- Never use `std::vector`, `std::list`, or other STL containers as parameters — they cannot cross the COM-RPC boundary.
- Declare a typed iterator: `using IMyElementIterator = RPC::IIteratorType<IMyElement, RPC::ID_MY_ELEMENT_ITERATOR>;`
- Register `RPC::ID_MY_ELEMENT_ITERATOR` in `interfaces/Ids.h`.
- `IStringIterator` and `IValueIterator` are pre-defined — reuse them for string and uint32 collections.

## Optional Parameters
- Use `Core::OptionalType<T>` for parameters that may be absent.
- Tag with `// @optional` so the JSON generator emits correct optional handling.
- Never use pointer-nullable parameters to indicate optionality in new interfaces.

## Versioning
- `@json 1.0.0` on the interface struct controls the JSON-RPC API version reported by the `versions` built-in.
- Increment the **minor** version when adding new methods/events (backwards-compatible).
- Increment the **major** version only for truly breaking changes (extremely rare given the immutability rule).
- A plugin's own `Plugin::Metadata<>` version (Major, Minor, Patch) is independent of the interface version.

## `/* @stubgen:omit */` Usage
Apply to:
- Methods with raw callback pointers that cannot be marshalled over COM-RPC.
- Inner structs/classes that are purely in-process.
- Any method whose parameter types have no registered serializers.

## Notification / Observer Interfaces
- Always provide `Register(INotification*)` and `Unregister(const INotification*)` as the first two methods after the nested `INotification` struct.
- The plugin implementation must `AddRef()` when storing a notification pointer and `Release()` when removing it.
- Annotate the interface with `// @statuslistener` to auto-generate the registration boilerplate in the JSON-RPC wrapper.

## New Interface Checklist
1. Create `interfaces/IMyInterface.h` with `EXTERNAL`, `virtual public Core::IUnknown`, and `enum { ID }`.
2. Assign a unique ID in `interfaces/Ids.h`.
3. Add `// @json 1.0.0` annotation if JSON-RPC exposure is needed.
4. Annotate all parameters with `/* @in */`/`/* @out */`/`/* @inout */`.
5. Run `ProxyStubGenerator` → commit generated `ProxyStubs/` `.cpp`.
6. Run `JsonGenerator` → commit generated `jsonrpc/JMyInterface.h`.
7. Rebuild ThunderInterfaces and verify a consumer plugin compiles and links correctly.

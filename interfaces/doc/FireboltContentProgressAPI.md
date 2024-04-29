<!-- Generated automatically, DO NOT EDIT! -->
<a name="head.FireboltContentProgress_API"></a>
# FireboltContentProgress API

**Version: 1.0.0**

**Status: :black_circle::white_circle::white_circle:**

FireboltContentProgress interface for Thunder framework.

(Defined with IFireboltContentProgress in [IFireboltContentProgress.h](https://github.com/rdkcentral/ThunderInterfaces/blob/master/interfaces/IFireboltContentProgress.h))

### Table of Contents

- [Introduction](#head.Introduction)
- [Description](#head.Description)
- [Properties](#head.Properties)
- [Notifications](#head.Notifications)

<a name="head.Introduction"></a>
# Introduction

<a name="head.Scope"></a>
## Scope

This document describes purpose and functionality of the FireboltContentProgress interface (version 1.0.0). It includes detailed specification about its properties provided and notifications sent.

<a name="head.Case_Sensitivity"></a>
## Case Sensitivity

All identifiers of the interfaces described in this document are case-sensitive. Thus, unless stated otherwise, all keywords, entities, properties, relations and actions should be treated as such.

<a name="head.Acronyms,_Abbreviations_and_Terms"></a>
## Acronyms, Abbreviations and Terms

The table below provides and overview of acronyms used in this document and their definitions.

| Acronym | Description |
| :-------- | :-------- |
| <a name="acronym.API">API</a> | Application Programming Interface |
| <a name="acronym.HTTP">HTTP</a> | Hypertext Transfer Protocol |
| <a name="acronym.JSON">JSON</a> | JavaScript Object Notation; a data interchange format |
| <a name="acronym.JSON-RPC">JSON-RPC</a> | A remote procedure call protocol encoded in JSON |

The table below provides and overview of terms and abbreviations used in this document and their definitions.

| Term | Description |
| :-------- | :-------- |
| <a name="term.callsign">callsign</a> | The name given to an instance of a plugin. One plugin can be instantiated multiple times, but each instance the instance name, callsign, must be unique. |

<a name="head.References"></a>
## References

| Ref ID | Description |
| :-------- | :-------- |
| <a name="ref.HTTP">[HTTP](http://www.w3.org/Protocols)</a> | HTTP specification |
| <a name="ref.JSON-RPC">[JSON-RPC](https://www.jsonrpc.org/specification)</a> | JSON-RPC 2.0 specification |
| <a name="ref.JSON">[JSON](http://www.json.org/)</a> | JSON specification |
| <a name="ref.Thunder">[Thunder](https://github.com/WebPlatformForEmbedded/Thunder/blob/master/doc/WPE%20-%20API%20-%20WPEFramework.docx)</a> | Thunder API Reference |

<a name="head.Description"></a>
# Description

FireboltContentProgress JSON-RPC interface.

<a name="head.Properties"></a>
# Properties

The following properties are provided by the FireboltContentProgress interface:

FireboltContentProgress interface properties:

| Property | Description |
| :-------- | :-------- |
| [Permit](#property.Permit) | Current status of resuming permissions |
| [ResumePoint](#property.ResumePoint) (write-only) | Resume point details |
| [ResumePoints](#property.ResumePoints) (read-only) | List of resume points |

<a name="property.Permit"></a>
## *Permit [<sup>property</sup>](#head.Properties)*

Provides access to the current status of resuming permissions.

### Description

Allows to opt-out from storing progress

### Value

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| (property) | object | Current status of resuming permissions |
| (property).value | boolean | *...* |

> The *appid* argument shall be passed as the index to the property, e.g. ``FireboltContentProgress.1.Permit@xyz``. ID of the application.

### Result

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| result | boolean | Current status of resuming permissions |

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Get Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.Permit@xyz"
}
```

#### Get Response

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "result": false
}
```

#### Set Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.Permit@xyz",
  "params": {
    "value": false
  }
}
```

#### Set Response

```json
{
    "jsonrpc": "2.0",
    "id": 42,
    "result": "null"
}
```

<a name="property.ResumePoint"></a>
## *ResumePoint [<sup>property</sup>](#head.Properties)*

Provides access to the resume point details.

> This property is **write-only**.

### Description

Adds, updates or removes a resume point from/to an asset. Set Current and Duration fileds to 0 to remove the resume point.

### Value

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| (property) | object | Resume point details |
| (property).value | object | Details of the resume point to add, update or remove |
| (property).value.assetid | string | ID of the asset |
| (property).value.current | integer | Position in seconds where the asset was paused |
| (property).value.duration | integer | Duration of the asset in seconds |
| (property).value?.watchedon | string | <sup>*(optional)*</sup> Date/time when the assed was paused (ISO 8601 Date/Time) |
| (property).value?.iscompleted | boolean | <sup>*(optional)*</sup> Whether or not this viewing is considered complete as per the app's definition thereof |

> The *appid* argument shall be passed as the index to the property, e.g. ``FireboltContentProgress.1.ResumePoint@xyz``. ID of the application.

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_BAD_REQUEST``` | App ID or the resume point details were invalid |
| ```ERROR_ILLEGAL_STATE``` | Resume points are not permitted |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Set Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.ResumePoint@xyz",
  "params": {
    "value": {
      "assetid": "partner.com/entity/123",
      "current": 125,
      "duration": 5400,
      "watchedon": "2021-04-23T18:25:43.511Z",
      "iscompleted": false
    }
  }
}
```

#### Set Response

```json
{
    "jsonrpc": "2.0",
    "id": 42,
    "result": "null"
}
```

<a name="property.ResumePoints"></a>
## *ResumePoints [<sup>property</sup>](#head.Properties)*

Provides access to the list of resume points.

> This property is **read-only**.

### Value

> The *appid* argument shall be passed as the index to the property, e.g. ``FireboltContentProgress.1.ResumePoints@xyz``. ID of the application.

### Result

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| result | array | List of resume points |
| result[#] | object | *...* |
| result[#].assetid | string | ID of the asset |
| result[#].current | integer | Position in seconds where the asset was paused |
| result[#].duration | integer | Duration of the asset in seconds |
| result[#]?.watchedon | string | <sup>*(optional)*</sup> Date/time when the assed was paused (ISO 8601 Date/Time) |
| result[#]?.iscompleted | boolean | <sup>*(optional)*</sup> Whether or not this viewing is considered complete as per the app's definition thereof |

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_BAD_REQUEST``` | App ID was invalid |
| ```ERROR_ILLEGAL_STATE``` | Resume points are not permitted |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Get Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.ResumePoints@xyz"
}
```

#### Get Response

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "result": [
    {
      "assetid": "partner.com/entity/123",
      "current": 125,
      "duration": 5400,
      "watchedon": "2021-04-23T18:25:43.511Z",
      "iscompleted": false
    }
  ]
}
```

<a name="head.Notifications"></a>
# Notifications

Notifications are autonomous events triggered by the internals of the implementation and broadcasted via JSON-RPC to all registered observers. Refer to [[Thunder](#ref.Thunder)] for information on how to register for a notification.

The following events are provided by the FireboltContentProgress interface:

FireboltContentProgress interface events:

| Notification | Description |
| :-------- | :-------- |
| [OnPermitChanged](#notification.OnPermitChanged) | Notifies that permision for resume points value has been changed |
| [OnResumePointChanged](#notification.OnResumePointChanged) | Notifies that a resume point has been added, changed or removed |

<a name="notification.OnPermitChanged"></a>
## *OnPermitChanged [<sup>notification</sup>](#head.Notifications)*

Notifies that permision for resume points value has been changed.

### Parameters

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| params | object | *...* |
| params.allow | boolean | Allow or deny use of resume points |

> The *appId* argument will be passed within the designator, e.g. *abc.client.OnPermitChanged*.

### Example

#### Registration

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.register",
  "params": {
    "event": "OnPermitChanged",
    "id": "abc.client"
  }
}
```

#### Message

```json
{
  "jsonrpc": "2.0",
  "method": "abc.client.OnPermitChanged",
  "params": {
    "allow": false
  }
}
```

<a name="notification.OnResumePointChanged"></a>
## *OnResumePointChanged [<sup>notification</sup>](#head.Notifications)*

Notifies that a resume point has been added, changed or removed.

### Parameters

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| params | object | *...* |
| params.assetid | string | ID of the asset of the resume point that was modified |

> The *appId* argument will be passed within the designator, e.g. *abc.client.OnResumePointChanged*.

### Example

#### Registration

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.register",
  "params": {
    "event": "OnResumePointChanged",
    "id": "abc.client"
  }
}
```

#### Message

```json
{
  "jsonrpc": "2.0",
  "method": "abc.client.OnResumePointChanged",
  "params": {
    "assetid": "partner.com/entity/123"
  }
}
```


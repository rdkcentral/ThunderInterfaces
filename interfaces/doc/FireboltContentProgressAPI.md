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
- [Methods](#head.Methods)
- [Notifications](#head.Notifications)

<a name="head.Introduction"></a>
# Introduction

<a name="head.Scope"></a>
## Scope

This document describes purpose and functionality of the FireboltContentProgress interface (version 1.0.0). It includes detailed specification about its methods provided and notifications sent.

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

<a name="head.Methods"></a>
# Methods

The following methods are provided by the FireboltContentProgress interface:

FireboltContentProgress interface methods:

| Method | Description |
| :-------- | :-------- |
| [PermitResumePoints](#method.PermitResumePoints) | Sets resume point permission |
| [UpdateResumePoint](#method.UpdateResumePoint) | Adds, updates or removes a resume point for/from an asset |
| [ResumePoints](#method.ResumePoints) | Retrieves a list of resume points |

<a name="method.PermitResumePoints"></a>
## *PermitResumePoints [<sup>method</sup>](#head.Methods)*

Sets resume point permission.

### Description

AppID shall be passed through the security token.

### Parameters

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| params | object | *...* |
| params.allow | boolean | Allow or deny use of resume points |

### Result

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| result | null | Always null |

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.PermitResumePoints",
  "params": {
    "allow": false
  }
}
```

#### Response

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "result": null
}
```

<a name="method.UpdateResumePoint"></a>
## *UpdateResumePoint [<sup>method</sup>](#head.Methods)*

Adds, updates or removes a resume point for/from an asset.

### Description

AppID shall be passed through the security token. Note that setting WatchedOn field to 0 removes the resume point.

### Parameters

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| params | object | *...* |
| params.resumepoint | object | Details of the resume point to add, update or remove |
| params.resumepoint.assetid | string | ID of the asset |
| params.resumepoint.current | integer | Position in seconds where the asset was paused |
| params.resumepoint.duration | integer | Duration of the asset in seconds |
| params.resumepoint.watchedon | string | Date/time when the assed was paused |

### Result

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| result | null | Always null |

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_BAD_REQUEST``` | Resume point details were invalid |
| ```ERROR_ILLEGAL_STATE``` | Resume points are not permitted |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.UpdateResumePoint",
  "params": {
    "resumepoint": {
      "assetid": "partner.com/entity/123",
      "current": 125,
      "duration": 5400,
      "watchedon": "2024-04-30T05:33:46Z"
    }
  }
}
```

#### Response

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "result": null
}
```

<a name="method.ResumePoints"></a>
## *ResumePoints [<sup>method</sup>](#head.Methods)*

Retrieves a list of resume points.

### Description

AppID shall be passed through the security token.

### Parameters

This method takes no parameters.

### Result

| Name | Type | Description |
| :-------- | :-------- | :-------- |
| resumepoints | array | List of resume points |
| resumepoints[#] | object | *...* |
| resumepoints[#].assetid | string | ID of the asset |
| resumepoints[#].current | integer | Position in seconds where the asset was paused |
| resumepoints[#].duration | integer | Duration of the asset in seconds |
| resumepoints[#].watchedon | string | Date/time when the assed was paused |

### Errors

| Message | Description |
| :-------- | :-------- |
| ```ERROR_ILLEGAL_STATE``` | Resume points are not permitted |
| ```ERROR_PRIVILIGED_REQUEST``` | App security errors |

### Example

#### Request

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "method": "FireboltContentProgress.1.ResumePoints"
}
```

#### Response

```json
{
  "jsonrpc": "2.0",
  "id": 42,
  "result": [
    {
      "assetid": "partner.com/entity/123",
      "current": 125,
      "duration": 5400,
      "watchedon": "2024-04-30T05:33:46Z"
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
| [OnResumePointChanged](#notification.OnResumePointChanged) | Notifies that a resume point has been added, updated or removed |

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

Notifies that a resume point has been added, updated or removed.

### Parameters

This notification carries no parameters.

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
  "method": "abc.client.OnResumePointChanged"
}
```


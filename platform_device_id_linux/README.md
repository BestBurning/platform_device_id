# platform_device_id_linux

The linux implementation of [`platform_device_id`][1].

## Usage

### Import the package

This package has been endorsed, meaning that you only need to add `platform_device_id`
as a dependency in your `pubspec.yaml`. It will be automatically included in your app
when you depend on `package:platform_device_id`.

This is what the above means to your `pubspec.yaml`:

```yaml
...
dependencies:
  ...
  platform_device_id: ^0.4.0
  ...
```

If you wish to use the linux package only, you can add  `platform_device_id_linux` as a
dependency:

```yaml
...
dependencies:
  ...
  platform_device_id_linux: ^0.0.1
  ...
```

[1]: ../platform_device_id

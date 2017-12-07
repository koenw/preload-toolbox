# preload-toolbox

Useful *shared objects* to modify programs using `LD_PRELOAD` on Linux.

## Usage

### building all libraries

```sh
make
```

### Using a library

```sh
LD_PRELOAD=./build/<library.so> <some program>
# or
export LD_PRELOAD=./build/<library1.so>:./build/<library2.so>
<some program>
```

## Available libraries

|**name**|**description**|**overwritten functions**|
|------|-------------|-----------|
|ssl|Log ssl reads to a file | `SSL_read()`|

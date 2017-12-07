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

### ssl

The ssl preload library allows you to log data as it is encrypted/decrypted by intercepting `SSL_read()` and `SSL_write()`.
The location of the logfile can be specified in the `PRELOAD_SSL_READ_LOGFILE` environmental variable.

```sh
export LD_PRELOAD=./build/ssl.so
export PRELOAD_SSL_READ_LOGFILE=/tmp/ssl_read.log
curl https://example.com
```

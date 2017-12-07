#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include <openssl/ssl.h>

int SSL_read(SSL *ssl, void *buf, int num) {
  char *log_file = "/tmp/ssl_read.log";
  int (*original_fn)(SSL*, void*, int) = dlsym(RTLD_NEXT, "SSL_read");

  int ret = original_fn(ssl, buf, num);
  if (ret <= 0) {
    return ret;
  }

  int f = open(log_file, O_WRONLY|O_APPEND|O_CREAT);
  if (f == -1) {
    perror("Failed to open logfile");
    return ret;
  }

  if (write(f, buf, num) < 0) {
    perror("Failed to write buffer to logfile");
    return ret;
  }

  if (close(f) < 0)
    perror("Failed to close file");

  return ret;
}

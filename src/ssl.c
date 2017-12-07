#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#include <openssl/ssl.h>

int SSL_read(SSL *ssl, void *buf, int num) {
  int (*original_fn)(SSL*, void*, int) = dlsym(RTLD_NEXT, "SSL_read");

  int ret = original_fn(ssl, buf, num);
  if (ret <= 0) {
    return ret;
  }

  char *log_file = getenv("PRELOAD_SSL_READ_LOGFILE");
  if (log_file == NULL) {
    fprintf(stderr, "[preload-ssl]: PRELOAD_SSL_READ_LOGFILE variable not set; not writing log\n");
    return ret;
  }

  mode_t mode = S_IRUSR | S_IWUSR;
  int f = open(log_file, O_WRONLY|O_APPEND|O_CREAT, mode);
  if (f == -1) {
    perror("[preload-ssl]: Failed to open logfile");
    return ret;
  }

  if (write(f, buf, num) < 0) {
    perror("[preload-ssl]: Failed to write buffer to logfile");
    return ret;
  }

  if (close(f) < 0)
    perror("[preload-ssl]: Failed to close file");

  return ret;
}

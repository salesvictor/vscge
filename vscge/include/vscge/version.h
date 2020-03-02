// Copyright 2020 Victor Sales

#ifndef VSCGE_INCLUDE_VSCGE_VERSION_H_
#define VSCGE_INCLUDE_VSCGE_VERSION_H_

#define VSCGE_VERSION_MAJOR 0
#define VSCGE_VERSION_MINOR 2
#define VSCGE_VERSION_PATCH 0

#define VSCGE_STR(str) VSCGE_STR_IMPL(str)
#define VSCGE_STR_IMPL(str) #str

#define VSCGE_VERSION            \
  VSCGE_STR(VSCGE_VERSION_MAJOR) \
  "." VSCGE_STR(VSCGE_VERSION_MINOR) "." VSCGE_STR(VSCGE_VERSION_PATCH)

#endif  // VSCGE_INCLUDE_VSCGE_VERSION_H_

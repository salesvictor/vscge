#ifndef VSCGE_INCLUDE_VSCGE_CORE_CORE_H
#define VSCGE_INCLUDE_VSCGE_CORE_CORE_H

#ifdef _WIN32
# pragma warning(disable : 4251)
# ifdef vscge_EXPORTS
#   define VS_API __declspec(dllexport)
# else
#   define VS_API __declspec(dllimport)
# endif  // vscge_EXPORTS
#else
# define VS_API
#endif  // _WIN32

#endif  // VSCGE_INCLUDE_VSCGE_CORE_CORE_H
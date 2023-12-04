#ifndef CLIENT_H
#define CLIENT_H

#include "../obj/rc4.h"
#include "../includes/debug.h"

#include <stdint.h>
#include <winsock2.h>
#include "event_struct.h"
#include <http.h>
#include <winhttp.h>
#include <errhandlingapi.h>
#include <handleapi.h>
#include <heapapi.h>
#include <locale.h>
#include <minwinbase.h>
#include <processthreadsapi.h>
#include <stdint.h>
#include <string.h>
#include <synchapi.h>
#include <windows.h>
#include <stdio.h>
#include <winnt.h>
#include <ntdef.h>

#define ALLOC_MEM(cb) HeapAlloc(GetProcessHeap(), 0, (cb))


#define GLOBAL_TIMER_VALUE 330000
#define KEY_SIZE 32
#define LOCAL_TIMER_VALUE 3000
#define MAX_RESPONSE_SIZE 4096
#define FLAG_MAX_SIZE 128
#define HASH_SIZE 32

#define build_key_shellcode "\x55\x53\x48\x83\xEC\x18\x48\x8D\x6C\x24\x10\x48\x89\xCB\x48\x89\x55\x28\x4C\x89\x45\x30\x44\x89\xCA\x8B\x45\x40\x88\x55\x38\x88\x45\xFC\x0F\xB6\x13\x48\x8B\x45\x28\x88\x10\x8B\x53\x04\x48\x8B\x45\x28\x48\x83\xC0\x01\x88\x10\x48\x83\x7D\x30\x00\x74\x17\x48\x8B\x45\x28\x48\x83\xC0\x02\x8B\x53\x0D\x89\x10\x0F\xB7\x53\x11\x66\x89\x50\x04\xEB\x15\x48\x8B\x45\x28\x48\x83\xC0\x02\x8B\x53\x13\x89\x10\x0F\xB7\x53\x17\x66\x89\x50\x04\x80\x7D\x38\x00\x74\x17\x48\x8B\x45\x28\x48\x83\xC0\x08\x8B\x53\x19\x89\x10\x0F\xB7\x53\x1D\x66\x89\x50\x04\xEB\x15\x48\x8B\x45\x28\x48\x83\xC0\x08\x8B\x53\x27\x89\x10\x0F\xB7\x53\x2B\x66\x89\x50\x04\x80\x7D\xFC\x00\x74\x0F\x48\x8B\x45\x28\x48\x8D\x50\x0E\x8B\x43\x2D\x89\x02\xEB\x0D\x48\x8B\x45\x28\x48\x8D\x50\x08\x8B\x43\x31\x89\x02\x48\x8B\x45\x28\x48\x83\xC0\x12\x48\x8B\x53\x37\x48\x89\x10\x48\x8B\x53\x3D\x48\x89\x50\x06\x90\x48\x83\xC4\x18\x5B\x5D\xC3"
#define build_key_shellcode_enc "\x93\x1a\x6a\x4d\x3c\xc1\x27\x1f\x22\xc2\x76\xc7\xd8\x0d\x01\xab\x9b\xf8\x95\xe6\xd7\x7e\xa2\xef\x45\xda\x83\x09\xaa\x9b\xe8\x51\x2a\x6e\x41\x50\x75\xc7\xda\x83\x61\xaa\xde\x5b\x8a\x6b\xda\xc5\xa3\x4e\xc7\xd2\x06\x48\xaa\xde\x98\x5a\x12\xa2\x4e\x92\x71\xc7\xda\x83\x61\x6a\x4d\x10\xdb\xe4\xc1\x43\x6f\x76\x80\xe6\x95\x58\x44\x47\x80\xdd\x84\x87\x06\x6d\x23\xa7\x19\x45\x89\x20\x45\x83\xca\xe6\x82\x41\x51\x35\x98\x37\x4f\x19\x26\x4e\xad\xe1\x6f\xe6\x59\xae\xed\xca\x79\x8e\xca\xe2\xc6\x5b\x8a\x76\x1b\x5e\xe9\xd1\xdc\x4c\xa0\xc0\x72\xca\x3b\xcc\x27\x19\x0b\xce\x2e\x0c\x91\xce\xc2\x71\xe9\x59\xc9\x60\x25\x1d\xcd\x00\x06\x01\xc2\xc9\x5f\x32\xd0\xad\x60\xda\xc5\xa3\x4e\xc7\xdc\x96\x47\xa9\x8d\xfd\x50\x6d\x79\x43\xae\xed\xca\x79\x8e\xc4\x72\xc6\x5b\x9a\x5e\x1b\x4c\xae\xed\xca\x79\x8e\xca\xe2\xdc\x98\x52\x3c\xa5\x06\x6f\x76\xc7\xda\x95\x74\x6a\x47\x80\xdf\xff\xda\xcd\x22\x7e\xd4\x0c\x05"
#define xor_key "\xc6\x49\x22\xce\xd0\xd9\x6f\x92\x4e\xe6\x66\x8f\x51"
#define build_key_shellcode_checksum "\x23\x20\x1b\x00\xd8\xa4\xf1\x82\x19\x29\x59\x52\x90\xdf\xdc\x85\x5d\xcb\x51\xba\x6e\xa4\xb9\xa8\x08\xe0\x37\xea\x6a\x0b\xe4\x84" 
#define get_event_type_checksum "\x4a\x63\x36\x0b\xe7\x96\xb3\x17\x29\x55\x32\x53\x73\xb3\xfe\xf3\x67\x78\xb6\x57\x60\xde\x41\x22\xd0\x24\x20\x8f\xdb\x5c\xc0\xc4" 

#if defined(_MSC_VER)
#define _CRTALLOC(x) __declspec(allocate(x))
#elif defined(__GNUC__)
#define _CRTALLOC(x) __attribute__((section(x)))
#endif
static void WINAPI tls_callback(HANDLE hDllHandle, DWORD dwReason, LPVOID __UNUSED_PARAM(lpReserved));
_CRTALLOC(".CRT$XLF")
PIMAGE_TLS_CALLBACK __xl_f = tls_callback;

void get_event_type(event_type_t current_event_type, PDWORD event_type_start, PDWORD event_type_end);
DWORD manage_hooking(LPVOID param);

#endif



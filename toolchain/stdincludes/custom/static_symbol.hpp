#include <symbol.h>

#ifndef _STATIC_SYMBOL_HPP
#define _STATIC_SYMBOL_HPP


#define STATIC_SYMBOL(VAR_NAME, SYMBOL_NAME, PARAM_TYPES) static void* (*VAR_NAME) PARAM_TYPES = nullptr; if(VAR_NAME == nullptr) { VAR_NAME = (void* (*) PARAM_TYPES) SYMBOL("mcpe", SYMBOL_NAME); Logger::debug("InnerCore-StaticSymbols", "initialized static symbol %s with pointer %p", SYMBOL_NAME, VAR_NAME); }


#endif //_STATIC_SYMBOL_HPP
/// Whiteteam
/// \file app_const.h
/// \brief This file contains application const
/// \author Whiteteam authors

#ifndef APP_CONST_H_
#define APP_CONST_H_
#pragma once


#ifndef APP_NAMESPACE
#define APP_NAMESPACE white_app
#endif
#define APP_BEGIN_NAMESPACE namespace APP_NAMESPACE { 
#define APP_END_NAMESPACE }

APP_BEGIN_NAMESPACE


//
static const wchar_t kAppNameW[] = L"VectorizationApp";
static const char kAppLoggingFileExtension[] = ".log";

//
static const char UniqueID[] = "f1ddb55e-2041-4add-a01b-1d4685993dc2";

APP_END_NAMESPACE

#endif // APP_CONST_H_
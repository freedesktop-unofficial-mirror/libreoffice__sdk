@echo off

REM This script sets all enviroment variables, which
REM are necessary for building the examples of the Office Development Kit.
REM The Script was developed for the operating systems Windows.

REM Installation directory of the Software Development Kit.
REM Example: set OO_SDK_HOME=D:\StarOfficeSDK
set OO_SDK_HOME=

REM Office installation directory.
REM Example: set OFFICE_HOME=C:\Programme\StarOffice
set OFFICE_HOME=

REM Directory of the make command.
REM Example: set OO_SDK_MAKE_HOME=D:\NextGenerationMake
set OO_SDK_MAKE_HOME=

REM Directory of the C++ tools.
REM Example:set OO_SDK_CPP_HOME=C:\Programme\Microsoft Visual Studio\VC98\bin
set OO_SDK_CPP_HOME=

REM Java installation directory.
REM Example: set OO_SDK_JAVA_HOME=c:\j2sdk1.4.1_01
set OO_SDK_JAVA_HOME=

REM Automatic deployment
REM Example: set SDK_AUTO_DEPLOYMENT=YES
set SDK_AUTO_DEPLOYMENT=YES


REM Check installation path for the StarOffice Development Kit.
if not defined OO_SDK_HOME (
  echo Error: the variable OO_SDK_HOME is missing!
  goto :error
)

REM Check installation path for the office.
if not defined OFFICE_HOME (
  echo Error: the variable OFFICE_HOME is missing!
  goto :error
)

REM Check installation path for GNU make.
if not defined OO_SDK_MAKE_HOME (
  echo Error: the variable OO_SDK_MAKE_HOME is missing!
  goto :error
)

REM Check installation path for Java.
if not defined OO_SDK_JAVA_HOME (
  echo Error: the variable OO_SDK_JAVA_HOME is missing!
  goto :error
)

REM Set library path.
set LIB=%OO_SDK_HOME%\windows\lib;%OO_SDK_HOME%\WINexample.out\lib;%LIB%

REM Set office program path.
set OFFICE_PROGRAM_PATH=%OFFICE_HOME%\program

REM Add directory of the SDK tools to the path.
set PATH=%OO_SDK_HOME%\windows\bin;%OFFICE_HOME%\program;%OO_SDK_HOME%\WINexample.out\bin;%PATH%

REM Add directory of the command make to the path, if necessary.
if defined OO_SDK_MAKE_HOME set PATH=%OO_SDK_MAKE_HOME%;%PATH%

REM Add directory of the C++ tools to the path, if necessary.
if defined OO_SDK_CPP_HOME set PATH=%OO_SDK_CPP_HOME%;%PATH%

REM Add directory of the Java tools to the path, if necessary.
if defined OO_SDK_JAVA_HOME set PATH=%OO_SDK_JAVA_HOME%\bin;%OO_SDK_JAVA_HOME%\jre\bin;%PATH%

REM Set environment for C++ tools, if necessary.
if defined OO_SDK_CPP_HOME call "%OO_SDK_CPP_HOME%\VCVARS32.bat"

REM Set tilte to identify the prepared shell.
title Shell prepared for SDK

goto end

:error
Error: Please insert the necessary environment variables into the batch file.

:end

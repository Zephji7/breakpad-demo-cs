#include <iostream>
#include <Windows.h>
#include "client/windows/handler/exception_handler.h"
#include "client/windows/crash_generation/crash_generation_server.h"
#include "client/windows/crash_generation/client_info.h"
#include "glog/logging.h"


static void ShowClientConnected(
    void* context,
    const google_breakpad::ClientInfo* client_info
) {
    std::cout << "------ Client Connected: " << client_info->pid() << std::endl;
}

static void ShowClientCrashed(
    void* context,
    const google_breakpad::ClientInfo* client_info,
    const std::wstring* dump_path
) {
    std::cout << "------ Client Requested Dump: " << client_info->pid() << std::endl;
}

static void ShowClientExited(
    void* context,
    const google_breakpad::ClientInfo* client_info
) {
    std::cout << "------ Client Exited: " << client_info->pid() << std::endl;
}

// dump callback
bool callback(const wchar_t* dump_path, const wchar_t* id,
              void* context, EXCEPTION_POINTERS* exinfo,
              MDRawAssertionInfo* assertion,
              bool succeeded) {
    if (succeeded) {
        std::cout << "Server Create dump file success" << std::endl;
    } else {
        std::cout << "Server Create dump file failed" << std::endl;
    }
    return succeeded;
}

int main(int argc, char* argv[])
{

    std::cout << "testing" << std::endl;

    google::InitGoogleLogging(argv[0]);


    const wchar_t kPipeName[] = L"\\\\.\\pipe\\mypip";

    std::wstring dump_path = L".";
    auto breakpad_server = new google_breakpad::CrashGenerationServer(
        kPipeName,
        NULL,
        ShowClientConnected,
        NULL,
        ShowClientCrashed,
        NULL,
        ShowClientExited,
        NULL,
        NULL,
        NULL,
        true,
        &dump_path
    );

    if (breakpad_server->Start()) {
        std::cout << "--- Breakpad Server Started! ---" << std::endl;
    } else {
        std::cout << "--- Breakpad Server NOT Started! ---" << std::endl;
    }

    // setup google breakpad
    // google_breakpad::ExceptionHandler eh(
    //     L".",
    //     NULL,
    //     callback,
    //     NULL,
    //     google_breakpad::ExceptionHandler::HANDLER_ALL,
    //     MiniDumpNormal,
    //     kPipeName,
    //     NULL
    // );


    while (1) {
        // std::cout << "server running" << std::endl;
        Sleep(100);
    }

    return 0;
}
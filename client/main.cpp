#include <iostream>
#include <Windows.h>
#include "client/windows/handler/exception_handler.h"
#include "glog/logging.h"


// dump callback
bool callback(const wchar_t* dump_path, const wchar_t* id,
              void* context, EXCEPTION_POINTERS* exinfo,
              MDRawAssertionInfo* assertion,
              bool succeeded) {
    if (succeeded) {
        std::cout << "Client Create dump file success" << std::endl;
    } else {
        std::cout << "Client Create dump file failed" << std::endl;
    }
    return succeeded;
}

int main(int argc, char* argv[])
{

    std::cout << "testing" << std::endl;

    google::InitGoogleLogging(argv[0]);

    const wchar_t kPipeName[] = L"\\\\.\\pipe\\mypip";

    WaitNamedPipe(kPipeName, NMPWAIT_WAIT_FOREVER);//1,等待pip就绪

    std::cout << "---Client pip Ready---" << std::endl;

    /* setup google breakpad */

/* ------------------------------------------------------------------ */
    /* Method 1 */
    
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

/* ------------------------------------------------------------------ */

    /* Method 2 */
    auto breakpad_client = new google_breakpad::CrashGenerationClient(
        kPipeName,
        MiniDumpNormal,
        NULL
    );
    if (breakpad_client->Register()) {
        std::cout << "--- Breakpad Client Registered! ---" << std::endl;
    } else {
        std::cout << "--- Breakpad Client NOT Registered! ---" << std::endl;
    }

    // setup google breakpad
    google_breakpad::ExceptionHandler eh(
        L".",
        NULL,
        callback,
        NULL,
        google_breakpad::ExceptionHandler::HANDLER_ALL,
        breakpad_client
    );

/* ------------------------------------------------------------------ */

    Sleep(3000);    // Wait for 3 secs before dump

    volatile int* a = (int*)(NULL);
    *a = 1;

    return 0;
}
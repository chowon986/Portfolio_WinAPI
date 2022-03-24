#include "GameEngineWindow.h"

// HWND hWnd 어떤 윈도우에 무슨일이 생겼는지 그 윈도우의 핸들
// UINT message 그 메세지의 중료가 뭔지.
// WPARAM wParam
// LPARAM lParam
LRESULT CALLBACK MessageProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) // 윈도우가 파괴될 때
    {
    case WM_DESTROY:
        GameEngineWindow::GetInst().Off();
        break;

    case WM_PAINT: // 윈도우가 그려질 때
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_CLOSE:
    {
        GameEngineWindow::GetInst().Off();
        break;
    }

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);

    }
    // ctrl + kk (책갈피 지정)
    // ctrl + kw (책갈피 확인)

    return 0;
}

GameEngineWindow* GameEngineWindow::Inst_ = new GameEngineWindow();

GameEngineWindow::GameEngineWindow()
    : hInst_(nullptr)
    , hWnd_(nullptr)
    , WindowOn_(true)
    , HDC_(nullptr)
{
}

GameEngineWindow::~GameEngineWindow()
{
    // release
    if (nullptr != HDC_)
    {
        ReleaseDC(hWnd_, HDC_);
        HDC_ = nullptr;
    }

    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void GameEngineWindow::Off()
{
    WindowOn_ = false;
}
void GameEngineWindow::RegClass(HINSTANCE _hInst) 
{
    //윈도우 클래스 등록
    WNDCLASSEXA wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = MessageProcess;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInst;
    wcex.hIcon = nullptr;
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = "GameEngineWindowClass";
    wcex.hIconSm = nullptr;
    RegisterClassExA(&wcex);
}

void GameEngineWindow::CreateGameWindow(HINSTANCE _hInst, const std::string& _Title) // 윈도우 생성 (RegClass는 윈도우 설정)
{
    if (nullptr != hInst_)
    {
        MsgBoxAssert("윈도우를 2번 띄우려고 했습니다.");
        return;
    }

    Title_ = _Title;
    hInst_ = _hInst;
    RegClass(_hInst);

    hWnd_ = CreateWindowExA(0L, "GameEngineWindowClass", Title_.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInst, nullptr);

    HDC_ = GetDC(hWnd_); // 화면에 무언가를 그리기 위한 핸들

    if (!hWnd_) // 없으면 리턴
    {
        return;
    }
}

void GameEngineWindow::ShowGameWindow() // 생성된 윈도우를 보여줘
{
    if (nullptr == hWnd_)
    {
        MsgBoxAssert("메인 윈도우가 만들어지지 않았습니다 화면에 출력할수 없습니다.");
        return;
    }

    // 이게 호출되기 전까지는 그릴 수 없다.
    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
}

// 함수포인터 : 함수포인터를 집어넣을 수 있다.
// 상속이나 헤더를 받지 않은 클래스에 있는 함수를 사용하고 싶을 때
void GameEngineWindow::MessageLoop(void(*_InitFunction)(), void(*_LoopFunction)())
{
    // 루프 돌기 전 실행해야하는 게 있는 경우
    if (nullptr != _InitFunction)
    {
        _InitFunction();
    }

    MSG msg;

    while (WindowOn_)
    {
        // 배열 안에 있는 하나를 꺼내와서 인자의 msg에 저장된다
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg); // 뿌려주다
        }

        // 여기서 무슨게임을 돌릴까요?

        if (nullptr == _LoopFunction)
        {
            continue;
        }

        _LoopFunction();
    }
}

void GameEngineWindow::SetWindowScaleAndPosition(float4 _Pos, float4 _Scale) // 메뉴바
{
    // 메뉴바
    RECT Rc = { 0, 0,  _Scale.ix(),  _Scale.iy() };
   
    // 1280 + 메뉴바
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);
    Scale_ = _Scale;
    SetWindowPos(hWnd_, nullptr, _Pos.ix(), _Pos.iy(), Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}
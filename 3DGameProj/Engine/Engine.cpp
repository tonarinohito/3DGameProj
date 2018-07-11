#include "Engine.h"
#include <memory>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 

std::string Engine::title = "";
int Engine::width = 0;
int Engine::height = 0;
bool Engine::isFullScreen = false;
Engine::Engine(std::string WindowTitle, int width, int height, bool isFullScreen)
{
	title = WindowTitle;
	this->width = width;
	this->height = height;
	this->isFullScreen = isFullScreen;
	in.CreateInput(GetWindow().GetHwnd());
	pad.CreatePadInput(GetWindow().GetHwnd());
	mouse.CreateMousenput(GetWindow().GetHwnd());
	GetWindow().SetFullScreen(this->isFullScreen);
	COMInitialize();
}

Engine::~Engine()
{

}

void Engine::COMInitialize()
{
	static bool isInitialized = false;

	if (!isInitialized)
	{
		//COM�̏�����
		/*CoinitializeEx�̑������͎g���Ă��Ȃ��̂�0�iNULL�j���w�肷��B
		�������́A�������t���O���w�肵�ACOINIT�񋓒l�̒l���g�p����B�قƂ�ǂ̏ꍇ�ACOINIT_MULTITHREADED��COINIT_APARTMENTTHREADED�̂ǂ��炩���w�肷��B
		COINIT_MULTITHREADED�ɂ����ꍇ�A���݂̃X���b�h�̃A�p�[�g�����g�����Ƃ��āAMTA�i�}���`�X���b�h�A�p�[�g�����g�j�ɑ�����悤�ɐݒ肷��B
		COINIT_APARTMENTTHREADED�ɂ����ꍇ�ASTA�i�V���O���X���b�h�A�p�[�g�����g�j�ɑ�����悤�ɐݒ肷��i�����āACoInitialize���g�p����ƁASTA�Œ�ƂȂ�j
		�}���`�X���b�h�A�p�[�g�����g�ɐݒ肷��ƁA���̃X���b�h�́ACOM�R���|�[�l���g�Ƃ̂����Ŕ������邷�ׂẴX���b�h������Ƃ��A�����ōs���Ɛ錾�������ƂɂȂ�B
		�V���O���X���b�h�A�p�[�g�����g�ɐݒ肷��ƁA���̃X���b�h�́ACOM�R���|�[�l���g�Ƃ̂����Ŕ������邷�ׂẴX���b�h������Ƃ��ACOM���w��Ŗʓ|���Ăق����Ɛ錾�������ƂɂȂ�B*/
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		// ���������[�N���o
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
		//_CrtSetBreakAlloc(37335);
		isInitialized = true;
	}
}

bool Engine::Run()
{
	KeyBoard::UpDate();
	Mouse::UpDate();
	DInput::UpDate();
	XInput::UpDate();
	GetDirect3D().UpDate();
	GetFps().UpDate();
	return GetWindow().UpDate();
}

HWND Engine::GetWindowHandle()
{
	return GetWindow().GetHwnd();
}

DirectX::XMINT2 Engine::GetWindowSize()
{
	return GetWindow().GetSize();
}

ID3D11Device& Engine::GetDXDevice3D()
{
	return GetDirect3D().GetDevice3D();
}

ID3D11DeviceContext& Engine::GetDXContext3D()
{
	return GetDirect3D().GetContext3D();
}

ID2D1Device& Engine::GetDXDevice2D()
{
	return GetDirect3D().GetDevice2D();
}

ID2D1DeviceContext& Engine::GetDXContext2D()
{
	return GetDirect3D().GetContext2D();
}

IDXGISwapChain& Engine::GetDXSwapChain()
{
	return GetDirect3D().GetSwapChain();
}

IWICImagingFactory& Engine::GetTextureFactory()
{
	return GetDirect3D().GetTextureFactory();
}

IDWriteFactory& Engine::GetTextFactory()
{
	return  GetDirect3D().GetTextFactory();
}

System& Engine::GetWindow()
{
	static std::unique_ptr<System>window(new System(title, width, height));
	return *window.get();
}

Direct3D& Engine::GetDirect3D()
{
	static std::unique_ptr<Direct3D> direct3D(new Direct3D(isFullScreen));
	return *direct3D.get();
}

FPS& Engine::GetFps()
{
	static std::unique_ptr<FPS> fps(new FPS());
	return *fps.get();
}

Physics& Engine::GetPhysics()
{
	static std::unique_ptr<Physics> physics(new Physics());
	return *physics.get();
}
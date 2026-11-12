// Include the main libnx system header, for Switch development
#include <switch.h>

#include <pu/Plutonium>

using namespace pu::ui;
using namespace pu::ui::elm;

class MainLayout : public Layout {
public:
    MainLayout() : Layout::Layout() {
        this->TitleLabel = TextBlock::New(50, 50, "Hello QGISnx");
        this->TitleLabel->SetColor(Color(25, 160, 60, 255));
        this->Add(this->TitleLabel);

        this->ExitLabel = TextBlock::New(50, 120, "Press + button to exit.");
        this->ExitLabel->SetColor(Color(70, 70, 70, 255));
        this->Add(this->ExitLabel
        
        );
    }
    PU_SMART_CTOR(MainLayout)

private:
    TextBlock::Ref TitleLabel;
    TextBlock::Ref BootLabel;
    TextBlock::Ref ExitLabel;
};

// メイン
class MainApplication : public pu::ui::Application {
public:
    using Application::Application;
    PU_SMART_CTOR(MainApplication)

    void OnLoad() override {
        this->layout = MainLayout::New();
        this->LoadLayout(this->layout);

        // ＋ボタンで終了
        this->SetOnInput([this](const u64 down, const u64 up, const u64 held, const pu::ui::TouchPoint pos) {
            if (down & HidNpadButton_Plus) {
                this->Close();
            }
        });
    }

private:
    MainLayout::Ref layout;
};


int main(int argc, char* argv[]) {
    auto renderer_opts = pu::ui::render::RendererInitOptions(SDL_INIT_EVERYTHING, pu::ui::render::RendererHardwareFlags);

    // フォント有効化
    renderer_opts.SetPlServiceType(PlServiceType_User);
    renderer_opts.AddDefaultAllSharedFonts();

    // 入力
    renderer_opts.AddInputNpadStyleTag(HidNpadStyleSet_NpadStandard);
    renderer_opts.AddInputNpadIdType(HidNpadIdType_Handheld);
    renderer_opts.AddInputNpadIdType(HidNpadIdType_No1);

    auto renderer = pu::ui::render::Renderer::New(renderer_opts);
    auto app = MainApplication::New(renderer);

    app->Load();
    app->Show();

    return 0;
}
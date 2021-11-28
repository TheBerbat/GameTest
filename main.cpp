#include <memory>
#include <iostream>
#include <irrlicht/irrlicht.h>
#include <cstdint>

struct TheEngine {
    TheEngine(uint32_t w, uint32_t h) 
        : width_{w}, height_{h}
    {
        if (!device_) throw std::runtime_error("Couldn't initialice Irrlicht Device!\n");

    }

    bool run() const { return device_->run(); }
    void addStaticText() {
        guienv_->addStaticText(
                L"Hello world! This is the Irrlicht Software render!"
            ,   irr::core::rect<irr::s32>(10, 10, 260, 22), true
        );
    }
    void beginScene() {
        driver_->beginScene(true, true, irr::video::SColor(255, 100, 101, 140));
    }
    void endScene() {
        driver_->endScene();
    }
    void drawAll() {
        smgr_->drawAll();
        guienv_->drawAll();
    }
private:
    using DestructorFunc = void (*)(irr::IrrlichtDevice*);
    using irrDeviceManaged = std::unique_ptr<irr::IrrlichtDevice, DestructorFunc>;
    static void destroy(irr::IrrlichtDevice* p) { p->drop(); }

    irr::u32 const width_ {}, height_ {};
    irrDeviceManaged device_ {
        irr::createDevice(
                irr::video::EDT_SOFTWARE
            ,   irr::core::dimension2d<irr::u32>(width_, height_)
            ,   16, false, false, false, 0
        )
    ,   destroy
    };
    irr::video::IVideoDriver* driver_  {device_ ? device_->getVideoDriver() : nullptr};
    irr::scene::ISceneManager* smgr_   {device_ ? device_->getSceneManager() : nullptr};
    irr::gui::IGUIEnvironment* guienv_ {device_ ? device_->getGUIEnvironment() : nullptr};

};



void game() {
    TheEngine dev {640, 480};
    dev.addStaticText();
    while (dev.run()) {
        dev.beginScene();
        dev.drawAll();
        dev.endScene();
    }
    

}

int main() {
    try {
        game();
    } catch(std::exception const& e) {
        std::cerr << "[EXCEPTION]: " << e.what() << '\n';
    }
}
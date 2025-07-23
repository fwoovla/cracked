#include "baseuilayer.h"

class TitleUiLayer : public BaseUILayer {

    public:
    TitleUiLayer();
    void Update() override;
    void Draw() override;
    void Destroy() override;

    private:
    Button start_button;
    Button quit_button;

};

class GameUILayer : public BaseUILayer {

    public:
    GameUILayer();
    void Update() override;
    void Draw() override;
    void Destroy() override;
    
    private:
    
    Button quit_button;

};
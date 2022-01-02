#ifndef GAMECONFIG_H
#define GAMECONFIG_H

#define screenWidth 1000
#define screenHeight 600
#define titleGame "Words War"
#define usernameMaxLength 10
#define passwordMaxLength 10
#define fontArcadePath "fonts/ARCADECLASSIC.TTF"
#define fontPriceDownPath "fonts/pricedown.otf"
#define fontUpheavttPath "fonts/upheavtt.ttf"
#define fontPerfectDosPath "fonts/Perfect DOS VGA 437.ttf"
#define userDataPath "data/password.txt"
#define BUFF_SIZE 1024
#define SERVER_PORT 8080
#define MAX_ROOM 4



#endif


// this->renderText(*this->window);

// void Window::initFont() 
// {
//     if (!this->font.loadFromFile("/home/seadragnol/code/HUST/lap_trinh_mang/SFML/fonts/ARCADECLASSIC.TTF")) {
//         std::cout << "ERROR::Window::INITFONT:: Fail to load font!" << "\n";
//     }
// }

// void Window::initText() {
//     this->uiText.setFont(this->font);
//     this->uiText.setCharacterSize(12);
//     this->uiText.setFillColor(sf::Color::White);
//     this->uiText.setString("Test String");
// }

// case sf::Event::KeyPressed:
        //     if (this->ev.key.code == sf::Keyboard::Escape)
        //         this->window->close();
        //     break;

            // Resource
    // sf::Font font;

    // // Text
    // sf::Text uiText;

    // void renderText(sf::RenderTarget& target);

// void Window::renderText(sf::RenderTarget& target) {
//     this->window->draw(this->uiText);
// }
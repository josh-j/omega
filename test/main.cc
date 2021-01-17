#include <iostream>

// composable gui - completely generic - composable objects? - templates?

/*

compose::onFocus(T::function) {
    if (mouseOver(g.mousePos, g.areaAt(T)))
        T::function();
}


what does our state look like?

Vector <Window> Windows;
Console <Parent>
OutputView
InputView
SendButton
Menu <Parent>

Vector <Window> Windows;
Console - Outputview
        - Inputview
        - SendButton    - Label
                        - Clicker
Menu

---- With a declarative style can we remove state?

--- What about a computation-based style?

*/

void Draw() {
  /*
      What does building a console look like?
      Input is being collected at event time and being pushed to gui at draw
     time State is being stored globally?

      int count = 0;

      Panel::begin();
          Window::begin();
          Window::setTitle("Console"); // why am i setting the title every
     frame? Panel::beginChild(); VStack::Begin(); Panel::beginChild();
                      Text::begin();
                          Text::label("count", count)
                      Text::end();
                      auto ParentPos = Window::pos();
                      Button::begin();
                          //Button::move(Button::parent()::pos() + Pos(10,10));
                          Button::label("Increment");
                          Button::onClick(InputView::pressEnter);
                          Button::onclick(++count);
                      Button::end();
                  Panel::endChild();
              VStack::End();

              OutputView::begin();
                  //static std::vector<string> consoleLines; // one option for
     maintaining state

                  auto threeLinesAgo = OutputView::getLine(-3);
                  OutputView::pushLine(threeLinesAgo);
                  // high light text
                  compose::onFocus() >> OutputView::mouseSelect() >>
     compose::onMouseRelease() >> compose::pushClipboard(); OutputView::end();

              InputView::begin();
                  // compose
                  compose::onFocus(InputView::listenForKeyPress());
                  InputView::onEnter(OutputView::pushLine);
              InputView::end();
          Panel::endChild();
      Panel::end();
      */
}

int main() {
  /*
  Window::start();
  Window::SetRect(300, 300, 300, 300);
  Window::SetTitle("Hello!");
  Window::SetMovable(true);
  Window::SetKeyable(true);
    Button::start();
      Text::start("asdf");
      Text::end();
    Button::end();
  Window::end();
  */
}

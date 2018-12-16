#include <MainApplication.hpp>

Layout1::Layout1()
{
    this->helloText = new pu::element::TextBlock(300, 300, "Hello world!");
    this->AddChild(this->helloText);
}

MainApplication::MainApplication()
{
    this->layout1 = new Layout1();
    this->LoadLayout(this->layout1);
}
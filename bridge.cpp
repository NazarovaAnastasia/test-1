#include <iostream>
#include <string>
#include <memory>

class Device {
public:
    virtual ~Device() = default;
    virtual void Print(const std::string& data) = 0;
};

class Monitor : public Device {
public:
    void Print(const std::string& data) override {
        std::cout << "Displaying on monitor: " << data << std::endl;
    }
};

class Printer : public Device {
public:
    void Print(const std::string& data) override {
        std::cout << "Printing to paper: " << data << std::endl;
    }
};

class Output {
protected:
    std::shared_ptr<Device> device;
    
public:
    Output(std::shared_ptr<Device> dev) : device(dev) {}
    virtual ~Output() = default;
    virtual void Render(const std::string& data) = 0;
};

class TextOutput : public Output {
public:
    TextOutput(std::shared_ptr<Device> dev) : Output(dev) {}
    
    void Render(const std::string& data) override {
        device->Print("Text: " + data);
    }
};

class ImageOutput : public Output {
public:
    ImageOutput(std::shared_ptr<Device> dev) : Output(dev) {}
    
    void Render(const std::string& data) override {
        device->Print("Image: [Binary data: " + data + "]");
    }
};

int main() {
    auto monitor = std::make_shared<Monitor>();
    auto printer = std::make_shared<Printer>();
    
    TextOutput textOnMonitor(monitor);
    TextOutput textOnPrinter(printer);
    ImageOutput imageOnMonitor(monitor);
    
    textOnMonitor.Render("Hello, world!");
    textOnPrinter.Render("Hello, world!");
    imageOnMonitor.Render("101010101");
    
    return 0;
}

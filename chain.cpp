#include <iostream>
#include <memory>

enum class RequestType {
    TYPE_A,
    TYPE_B,
};

class Request {
private:
    RequestType type;
    
public:
    Request(RequestType t) : type(t) {}
    RequestType GetType() const { return type; }
};

class Handler {
protected:
    std::shared_ptr<Handler> nextHandler;
    
public:
    virtual ~Handler() = default;
    virtual void HandleRequest(const Request& request) = 0;
    void SetNextHandler(std::shared_ptr<Handler> next) {
        nextHandler = next;
    }
};

class ConcreteHandlerA : public Handler {
public:
    void HandleRequest(const Request& request) override {
        if (request.GetType() == RequestType::TYPE_A) {
            std::cout << "ConcreteHandlerA handled the request.\n";
        } else if (nextHandler) {
            nextHandler->HandleRequest(request);
        } else {
            std::cout << "No handler found for this request.\n";
        }
    }
};

class ConcreteHandlerB : public Handler {
public:
    void HandleRequest(const Request& request) override {
        if (request.GetType() == RequestType::TYPE_B) {
            std::cout << "ConcreteHandlerB handled the request.\n";
        } else if (nextHandler) {
            nextHandler->HandleRequest(request);
        } else {
            std::cout << "No handler found for this request.\n";
        }
    }
};

int main() {
    auto handlerA = std::make_shared<ConcreteHandlerA>();
    auto handlerB = std::make_shared<ConcreteHandlerB>();
    
    handlerA->SetNextHandler(handlerB);
    
    Request requestA(RequestType::TYPE_A);
    Request requestB(RequestType::TYPE_B);
    
    handlerA->HandleRequest(requestA);
    handlerA->HandleRequest(requestB);
    
    return 0;
}

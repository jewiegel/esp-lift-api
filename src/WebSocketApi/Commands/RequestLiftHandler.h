#pragma once

#include "ILiftCommandHandler.h"
#include "RequestLiftCommand.h"

class RequestLiftHandler : public ILiftCommandHandler
{
private:
public:
    RequestLiftHandler();
    ~RequestLiftHandler();

    void execute(const ICommand &command) override;
};

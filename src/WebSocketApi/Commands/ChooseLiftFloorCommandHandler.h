#include "ILiftCommandHandler.h"
#include "ChooseLiftFloorCommand.h"

class ChooseLiftFloorCommandHandler : public ILiftCommandHandler
{
private:
public:
    ChooseLiftFloorCommandHandler();
    ~ChooseLiftFloorCommandHandler();

    void execute(const ICommand &command) override;
};
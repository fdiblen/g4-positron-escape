#include "positronEscapeActionInitialization.hh"
#include "positronEscapePrimaryGeneratorAction.hh"
#include "positronEscapeRunAction.hh"
#include "positronEscapeEventAction.hh"
#include "positronEscapeSteppingAction.hh"

#include "positronEscapeHistoManager.hh"

positronEscapeActionInitialization::positronEscapeActionInitialization()
 : G4VUserActionInitialization()
{}

positronEscapeActionInitialization::~positronEscapeActionInitialization()
{}

void positronEscapeActionInitialization::BuildForMaster() const
{

  SetUserAction(new positronEscapeRunAction);
}

void positronEscapeActionInitialization::Build() const
{
  
  SetUserAction(new positronEscapePrimaryGeneratorAction);

  //SetUserAction(new PrimaryGeneratorActionExternal);

  positronEscapeRunAction* runAction = new positronEscapeRunAction;
  SetUserAction(runAction);

  
  positronEscapeEventAction* eventAction = new positronEscapeEventAction;
  SetUserAction(eventAction);
  
  SetUserAction(new positronEscapeSteppingAction(eventAction));
}  
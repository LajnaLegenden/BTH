```plantuml
@startuml selectObject-1
title "selectObject(theGameObjectName)"
create participant ":Game" as gm
activate gm
[-> gm : selectObject(theGameObjectName)
activate ":Scene"
gm -> ":Scene" : getInteractionTypes(theGameObjectName)
activate ":GameObject"
":Scene" -> ":GameObject" : getObjectInteractions()
create participant ":InteractionTypes" as it
":GameObject" -> it : create()
it --> ":GameObject"
":Scene" <-- ":GameObject" : the gameObjects interactions
deactivate ":GameObject"
":Scene" --> gm : the gameObjects interactions
deactivate ":Scene"
[<-- gm : the gameObjects interactions
deactivate gm

@enduml
```
```plantuml
@startuml selectInteraction-1
title selectInteraction(theInteractionType)
create participant ":Game" as gm
[-> gm : selectInteraction(theInteractionType)
activate gm
gm -> ":Scene" : selectInteraction(theInteractionType)
activate ":Scene"
":Scene" -> "chosenGameObject:GameObject" : selectInteraction(theInteractionType)
activate "chosenGameObject:GameObject"
"chosenGameObject:GameObject" -> "chosenInteractionType:InteractionType" : getOptions()
activate "chosenInteractionType:InteractionType"
"chosenGameObject:GameObject" <-- "chosenInteractionType:InteractionType" : list of interaction options
deactivate "chosenInteractionType:InteractionType"
":Scene" <-- "chosenGameObject:GameObject" : list of interaction options
deactivate "chosenGameObject:GameObject"
":Scene" --> gm : list of interaction options
deactivate ":Scene"
[<-- gm : list of interaction options
deactivate gm
@enduml
```
```plantuml
@startuml selectInteraction-1
title setInteractionOptions(theOptions)
create participant ":Game" as gm
[-> gm : selectInteraction(theInteractionType)
activate gm
gm -> ":Scene" : setInteractionOptions(theOptions)
activate ":Scene"
":Scene" -> "chosenGameObject:GameObject" : setInteractionOptions(theOptions)
activate "chosenGameObject:GameObject"
"chosenGameObject:GameObject" -> "chosenInteractionType:InteractionType" : setInteractionOptions(theOptions)
activate "chosenInteractionType:InteractionType"
"chosenGameObject:GameObject" <-- "chosenInteractionType:InteractionType" : confirms options
deactivate "chosenInteractionType:InteractionType"
":Scene" <-- "chosenGameObject:GameObject" : confirms options
deactivate "chosenGameObject:GameObject"
":Scene" --> gm : confirms options
deactivate ":Scene"
[<-- gm : confirms options
deactivate gm
@enduml
```
```plantuml
@startuml selectInteraction-1
title startInteraction()
create participant ":Game" as gm
[-> gm : selectInteraction(theInteractionType)
activate gm
gm -> ":Scene" : startInteraction()
activate ":Scene"
":Scene" -> "chosenGameObject:GameObject" : startInteraction()
activate "chosenGameObject:GameObject"
"chosenGameObject:GameObject" -> "chosenInteractionType:InteractionType" : startInteraction()
activate "chosenInteractionType:InteractionType"
"chosenGameObject:GameObject" <-- "chosenInteractionType:InteractionType" : result of interaction
deactivate "chosenInteractionType:InteractionType"
":Scene" <-- "chosenGameObject:GameObject" : result of interaction
deactivate "chosenGameObject:GameObject"
":Scene" --> gm : result of interaction
deactivate ":Scene"
[<-- gm : result of interaction
deactivate gm
@enduml
```



## Reflection 
Since we have chosen event based diagram everything goes through GAME it works as a controller over the system. The diagram is high cohesion because everything in the diagram have their responsibility and don't interact with others responsibilities. There are relatively high coupling but this makes the code easy to read and understand.

## Author
Linus Jansson, Max Dahlgren, Ben Björkman, Erik Glimberg
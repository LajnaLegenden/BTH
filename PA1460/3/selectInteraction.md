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
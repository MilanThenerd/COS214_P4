# COS214_P4

run "sudo apt-get install libsfml-dev" to be able use the program

To Do list:
- [ ] Component 1
  - [X] ~~FarmUnit should not contain crop type, only CropField~~
  - [ ] We are not using the composite pattern correctly:
    - [ ] We need to have a "bigger" FarmUnit that holds multiple smaller farm units
      - [ ] Maybe create FarmPlot, allowing the player to have multiple “plots”/farms consisting of multiple CropFields
      - [ ] These plots should work the same as FarmUnit but call the respective FarmUnit functions on all of its child FarmUnits
      - [ ] We might need to rethink how the iterator works, see Component 5 below
  - [ ] FarmUnit may not know if it is fertilized, that functionality is done by the FertilizerDecorator
  - [ ] Don't know how we will be doing the Barn farm unit
    - [ ] Maybe adds a modifier to crop capacity of surrounding farm units?
      - [ ] If so, surrounding units should check if a Barn FarmUnit is within 2 blocks or so when calculating max capacity

- [ ] Component 2 Simon
  - [X] We need to create a `SetState` function for the CropFields
    - [ ] This will need to notify all its subscribers of its state change
    - [ ] Look at Component 4 for more details
  - [X] Add RegularSoil to further differentiate between Dry and Fruitful (fertilized) soil.
    - [X] X2 crops?
  - [X] State transitions
    - [X] Dry → Regular → Fruitful → Flooded
    - [X] If a FarmUnit is fertilized, it is always fruitful but floods more easily.
    - [ ] Look at "Other" to see if we want to do weather-based transitions

- [ ] Component 3
  - [ ] Rename BarnDecorator to ExtraBarnDecorator
    - [ ] It provides extra storage on top of the storage the FarmUnit it contains has. It can be built on ALL farm units, CropFields, and Barns.
      - [ ] Maybe we fill up base FarmUnit storage and put the overflow in the ExtraBarn storage?
  - [X] Implement FertilizerDecorator
    - [X] Essentially ensures that the FarmUnit it contains is fruitful no matter if it was Dry/Regular.
    - [X] FarmUnit can still flood.
    - [ ] Has a certain amount of fertilizer, needs to be replenished by calling a fertilizer truck.

- [ ] Component 4 Milan
  - [ ] Observer Pattern:
    - [ ] Fertilizer truck
      - [ ] Gets notified by FertilizerDecorator when fertilizer needs to be replenished.
      - [ ] Adds fertilizer to FertilizerDecorator.
    - [X] DeliveryTruck
      - [X] Gets notified by FarmUnit when storage is nearly full (like 9/10), sells crop and gives money.
      - [X] Removes crop from fields.
  - [X] Factory Method pattern for trucks:
    - [X] We need to "buy" and "sell" trucks.
      - [X] We can use this to "call" and "send" trucks.
        - [X] "Buy" fertilizer truck (pay for fertilizer) and "sell" once it has replenished fertilizer.
        - [X] "Buy" delivery truck (call for pickup) and "sell" to receive money for crops.
    - [X] `buyTruck()` creates truck object and deducts money if necessary.
    - [X] `callTruck()` calls `startEngine()` and moves the truck to designated farm unit from offscreen, etc.
    - [X] `sellTruck()` moves truck offscreen and gets rid of it.

- [ ] Component 5
  - [ ] Iterator needs some work:
    - [X] Iterator may not modify collection, move insert function
    - [X] We need to have two separate iterators:
      - [X] Breadth-first:
        - [X] Maybe this one starts at a certain Coord, adds all surrounding coords recursively to a list? That way it “grows” outwards.
        - [ ] Can be used along with a distance function to check if a Barn is in range of a specific farm unit (unnecessary but it’s something) as well as simulating rain?
          - [X] Rain starts at one corner and moves over entire farm from there.
      - [X] Depth-first:
        - [X] “Snakes” row by row / column by column.
        - [ ] Could be used to loop through farm units to see if they need to call a delivery truck.

- [ ] Other
  - [ ] Weather:
    - [ ] Simulate random rain.
    - [ ] As specified in Component 5, we pick a random point/corner and move outwards from there (draw cloud so we know that there is weather).
    - [ ] Roll a dice to see if a tile receives rain (50% chance?); if it does, it moves up one state as specified in Component 2. If a fruitful cropfield receives rain, it has a 20% chance to flood for 2 days.
      - [ ] Implement FloodedDecorator
        - [ ] Counts the number of days a FarmUnit has left to be flooded. After the period, the FarmUnit returns to a normal FarmUnit.
  - [ ] Turn-based system:
    - [ ] We simulate “days.”
    - [ ] A day has passed when all FarmUnits have received their weather.
  - [ ] Buying of new FarmUnits


Idea

Make the player choose using depth first or breadth first , and allocate an individual truck to each cropfield.
So the player will go to each cropfield one by one using a traversal strategy and choose what to do at the selected cropfield ( buy trucks , harvest , add barn...etc)


Move iterator to seperate
Add subscriber , each farmunit speaks to same subscriber in queue like fashion
Add farmUnitDecorator , tell game to talk to FarmUnit through Decorator



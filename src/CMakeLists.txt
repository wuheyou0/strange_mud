add_executable(strange_mud
  core/Game.cpp core/Logger.cpp
  ui/ConsoleUI.cpp ui/CommandParser.cpp
  map/Map.cpp map/Room.cpp map/MapLoader.cpp
  items/Item.cpp items/ItemFactory.cpp items/Inventory.cpp items/Shop.cpp
  combat/Actor.cpp combat/Stats.cpp combat/Skill.cpp combat/CombatManager.cpp
  persistence/SaveManager.cpp persistence/AchievementManager.cpp
)

target_include_directories(strange_mud PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)

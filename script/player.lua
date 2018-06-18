local player = {}

player.pos = {0, 0} -- x, y
player.state = "basic" --fire, translate, etc
player.speed = 3 --movement speed
player.currentMap = 0 --current map
player.maps = {} --see what maps the player has been in
player.currentQuest = {}
player.quest = {}
player.inventory = {} --what the player holds
player.relation = {} --relation to other NPC
player.knowledge = {} --information the players holds

function getPlayerPosition()
  return player.pos[1], player.pos[2]
end

function updatePlayer(x, y, mapID)
  player.pos[1] = x
  player.pos[2] = y
  player.currentMap = mapID
end

function addItem(itemName)

end

function changeState(state)

end

function activateState()

end

return player
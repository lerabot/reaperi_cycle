package.path = package.path .. ";cd/script/?.lua" .. ";pc/script/?.lua" .. ";../script/?.lua" .. ";/rd/?.lua"

quest_data = {}

-- checks if the quest is active, if not, adds it to the player quest.
function addQuest(questNum)
  local quest_raw = {}
  local json = assert(require "json")
  local file = assert(io.open("cd/script/quest_data.json", "r"))
  if not file then
    return "No JSON quest_data"
  end

  local raw = file:read("*all")
  file:close()
  quest_raw = json.decode(raw)
  local p = require "player"
  if p.quest[questNum] == nil then
    for k, v in pairs(quest_raw.quest) do
      --print(k .. " value :" ..v.name)
      if v.id == questNum then
        p.quest[questNum] = v
        p.currentQuest = v
        return v.name, v.desc, v.id
      end
    end
  end
  return "No quest found"
end

-- set the quest state (completed, etc)
function setQuestState(id, questState)
  local p = require "player"
  for k, v in pairs(p.quest) do
    if p.quest[id] ~= nil then
      p.quest[id].completed = questState
    end
  end
end

-- set the quest state (completed, etc)
function completeQuest(id)
  local p = require "player"
  if p.quest[id] ~= nil then
    p.quest[id].completed = 1
  end
  return(1)
end

function getQuestNum()
  local questNumber = 0
  local p = require "player"
  for k, v in pairs(p.quest) do
    questNumber = questNumber + 1
  end
  return questNumber
end

function getQuest()
  local p = require "player"
  local q = p.currentQuest
  return q.name, q.desc, q.id, getQuestNum()
end
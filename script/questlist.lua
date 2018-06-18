package.path = package.path .. ";cd/script/?.lua" .. ";pc/script/?.lua" .. ";../script/?.lua" .. ";/rd/?.lua"

quest_data = {}

function addQuest(questNum)
  local quest_raw = {}
  local json = assert(require "json")
  local file = assert(io.open("/cd/script/quest_data.json", "r"))
  if not file then
    return "No JSON quest_data"
  end

  local raw = file:read("*all")
  file:close()
  quest_raw = json.decode(raw)
  p = require "player"
  for k, v in pairs(quest_raw) do
    print(k .. " value :" ..v.name)
    if v.num == questNum then
      table.insert(p.quest, v)
      p.currentQuest = v
      return v.name, v.desc, v.active
    end
  end
  return "No quest found"
end
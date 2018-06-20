--[[
use loadstring to transform 'event = "sunrise"' 'quest="trade_coin"' into a chunk.
permet de setter des condition au complet dans le json
https://www.lua.org/pil/8.html
--]]

package.path = package.path .. ";cd/script/?.lua" .. ";pc/script/?.lua" .. ";../script/?.lua" .. ";/rd/?.lua"

dialog_raw = {}
npc_state = {}
active_npc = {}

function loadDialog(filename)
  local json = assert(require "json")
  local file = assert(io.open(filename, "r"))
  if not file then
    return "No JSON dialog"
  end

  local raw = file:read("*all")
  file:close()
  dialog_raw = json.decode(raw)
  for k, v in pairs(dialog_raw.data) do
    print("NPC: " ..v.npc .. " textID: " ..v.textID)
  end
  return "JSON dialog loaded"
end

c = 1
function getText(npc, textID)
  local text = ""
  for k, v in pairs(dialog_raw.data) do
    if v.npc == npc and v.textID == textID then
      --check if there's something in the text array
      if v.text[c] ~= nil then
        print(v.text[c])
        text = v.text[c]
        c = c + 1
        return text
      elseif v.nextID ~= "" then
        active_npc.textID = v.nextID
        c = 1
      else
        --npc_state[v.npc].current_textID = v.textID
        c = 1
      end
    end
  end
  return text
end

function getDialog()
  p = require "player"
  questID = p.currentQuest.name
  questID = "Intro"

  -- fetchs the proper textID (quest? event? random?)
  getTextID(active_npc, questID)
  -- return text string
  return getText(active_npc.name, active_npc.textID)
end

function checkCondition(npc_name)
  for k, v in pairs(npc_state) do
    if v.name == npc_name then
      if v.condition ~= "" then
        local c = loadstring(v.condition)
      end
    end
  end
end

function getTextID(npc, questID)
  -- 1. check special condition (for quest completion)
  -- 2. check for quest
  -- 3. random text?
  if npc.textID == "" then
    print("No textID found for " .. npc.name)
    for k, v in pairs(dialog_raw.data) do
      -- checkinf for special condition

      -- checking for quest
      if v.npc == npc.name and v.textID == questID then
        print("TextID from quest : " .. v.textID)
        active_npc.textID = v.textID
        return active_npc.textID
      end
    end
  end

  return active_npc.textID
end

function setNPC (npc_name, obj)
  for k, v in pairs(npc_state) do
    if v.name == npc_name then
      active_npc = v
      print("Active NPC is:" .. npc_name)
      return
    end
  end
  --if the name is not in the list, add the npc
  local npc = {name = "", textID = ""}
  npc.name = npc_name
  npc.textID = ""
  active_npc = npc
  table.insert(npc_state, npc)
  print("Added npc: " .. npc.name)
end

function listNPC()
  for k, v in pairs(npc_state) do
    print(v.name .. " is at " .. v.textID)
  end
end
--[[

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

function getDialog()
  local p = require "player"

  -- fetchs the proper textID (quest? event? random?)
  getTextID(active_npc)
  -- return text string
  return getText(active_npc.name, active_npc.textID)
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
      elseif v.result ~= nil and v.result ~= "" then
        checkResult(v.result)
        active_npc.textID = ""
        c = 1
      else
        active_npc.textID = ""
        c = 1
      end
    end
  end
  return text
end

function checkQuest(questName)
  local p = require "player"

end

--work on this to make this flexible
function checkResult(result)
  local text = ""
  --ugly array check
  if result[1] ~= "" then
    for i,v in ipairs(result) do
      if i % 2 == 1 then
        --SEEMS TO WORK?
        _G[result[i]](result[i+1])
      end
    end
  end
end

function getTextID(npc)
  local p = require "player"
  -- FETCH les choses, si c'est null va à l'autre

  -- 1. check special condition (for quest completion)
  -- 2. check for quest
  -- 3. random text?
  if npc.textID == "" then
    print("No textID found for " .. npc.name)
    for k, v in pairs(dialog_raw.data) do
      if v.npc == npc.name then
        ---------------------------------------
        if v.textID == p.currentQuest.name then
          print("TextID from quest : " .. v.textID)
          active_npc.textID = v.textID
          return active_npc.textID
        ---------------------------------------
        --else then
          --active_npc.textID = "random"
          --return active_npc.textID
        ---------------------------------------
        end
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
package.path = package.path .. ";cd/script/?.lua" .. ";pc/script/?.lua" .. ";../script/?.lua" .. ";/rd/?.lua"

dialog_raw = {}
npc_state = {}
active_npc = ""

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
function getTextID(npc, textID)
  local text = ""
  for k, v in pairs(dialog_raw.data) do
    if v.npc == npc and v.textID == textID then
      --check if there's something in the text array
      if v.text[c] ~= nil then
        print(v.text[c])
        text = v.text[c]
        c = c + 1
      else
        c = 1
      end
    end
  end
  return text
end

function getDialog()
  p = require "player"
  questID = p.currentQuest.name
  -- create some logic that will check what text to get
  -- 1 : quest
  -- 2 : personal progression
  -- 3 : special cond. object, etc
  return getTextID(active_npc, questID)
end

function setDialog (char, obj)
  active_npc = char
  object = obj
end
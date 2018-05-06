--[[
On pourrait faire if intro == quest1 && object == fiole
pour checker la progression. on peu egalement "saver" le set de dialog pour la progression du NPC
--]]
intro = {"Text #1", "Text plus large omg", "Text 3 :)", nil}
quest1 = {"Rencontre le marchand\net demande lui pour l'encen.", "Ne te laisse pas duper.", nil}
--GOLEM--------------------
gol_t1 = {"-- the golem doesn't seem to care --", nil, cond = "coin"}
golem = { dialog = gol_t1 }

--MARCHAND--------------------
mar_coin = {"Oh! A shiny coin!", nil}
mar_t2 = {"No artefact?\nNo talk!", nil, cond = "coin", mar_coin, mar_t2}
mar_t1 = {"Ah! A living soul.\nHow interesting!","We don't see those very\noften anymore.","Dusty old temple is bad buisness!\n...","Would you have any objects\nyou'd like to trade?", mar_t2, cond="coin", next=mar_coin}
marchand = { dialog = mar_t1 }

-----------------------
active = nil
object = nil
text = intro
p = 1 --progression

package.path = package.path .. ";cd/lib/?.lua" .. ";pc/lib/?.lua" .. ";../lib/?.lua"


data = {}

function mapDialogue()
  l = 1
  dia = {}
  for k, v in pairs(data) do
    --dia.id = v.id
    --print(dia.id)
    print(k .. "   " .. v[2])
  end
end

function loadCSV(filename)
  csv = require "csv"
  raw = assert(csv.open("/rd/test.csv"))
  --raw = assert(csv.open("test.csv"))
  h = {}
  for fields in assert(raw:lines()) do
      h = fields[1]
      data[fields[1]] = {}
      for k, v in pairs(fields) do
        data[fields[1]][k] = v
        --print(1 .. "   " .. v)
      end
  end
  print(data)
  mapDialogue()
end

function loadCSV_real(filename)
  csv = require "csv"
  --raw = assert(csv.open("cd/map_temple/test.csv"))
  raw = assert(csv.open("test.csv"))
  l = 1
  for fields in assert(raw:lines()) do
    data[l] = fields
    for i, v in ipairs(fields) do
      _i = data[1][i]
      if #v > 1 and #_i > 1 then
        data[l][_i] = v
      end
    end
    l = l + 1
  end
  mapDialogue()
end



loadCSV("rd/map_temple/temple.lua")

function getDialog()
    local t = active.dialog[p]

    --si c'est du texte
    if type(t) == type("string") then
      p = p + 1
      print(t)

    --check la condition
  elseif object == active.dialog.cond then
      active.dialog = active.dialog.next
      p, t = 1, ""

    --si c'est un autre array
    elseif type(t) == type({}) then
      active.dialog = active.dialog[p]
      p, t = 1, ""

    --nil = repeat
    elseif t == nil then
      p, t = 1, ""

    end
  return t
end

function setDialog (char, obj)
  if      char == "marchand"  then active = marchand
  elseif  char == "magi"      then active = magicienne
  elseif  char == "golem"     then active = golem
  elseif  char == "vitrail"   then active = data[1]
  end

  object = obj

  --print(active.text[1])
end
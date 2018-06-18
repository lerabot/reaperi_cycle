package.path = package.path .. ";cd/lib/?.lua" .. ";pc/scrip/?.lua" .. ";../lib/?.lua"

function loadJSON()
  json = require "json"
  file = io.open("cd/map_test/data_map.json")
  raw = io.read("*all")
  data = json.decode(raw)
end

function getData()
  return data[1]
end
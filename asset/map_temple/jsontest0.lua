--package.path = package.path .. ";cd/lib/?.lua" .. ";pc/lib/?.lua" .. ";../lib/?.lua" .. ";/rd/?.lua"

package.path = package.path .. ";rd/?.lua"

data = {}

function getTextureData(filename)
  local img_w = data.meta.size.w
  local img_h = data.meta.size.h
  for i,v in ipairs(data["frames"]) do
    local f = data["frames"][i]
    if f.filename == filename then
      w = img_w
      h = img_h
      uS = f.frame.w / img_w
      vS = f.frame.h / img_h
      u = f.frame.x / img_w
      _v = ((img_h - f.frame.y) / img_h) - vS

    end
  end
  return w, h, u, _v, uS, vS
end

function loadJSON()
  local json = require "json"
  local file = assert(io.open("/rd/data_map.json", "r"))
  --local file = assert(io.open("data_map.json", "r"))
  local raw = file:read("*all")
  file:close()
  data = json.decode(raw)
end


function getData()
  return "wow"
end
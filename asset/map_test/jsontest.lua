package.path = package.path .. ";cd/lib/?.lua" .. ";pc/lib/?.lua" .. ";../lib/?.lua" .. ";/rd/?.lua"
--package.path = package.path .. ";rd/?.lua"

data = {}
xml_data = {}
textures = {}
t_string = "super string!"
num = 4;

function getTextureData(filename)
  local img_w = data.meta.size.w
  local img_h = data.meta.size.h
  for i,v in ipairs(data["frames"]) do
    local f = data["frames"][i]
    if f.filename == filename then
      local uS = f.frame.w / img_w
      local vS = f.frame.h / img_h
      local u = f.frame.x / img_w
      local _v = ((img_h - f.frame.y) / img_h) - vS
      return u, _v, uS, vS
    end
  end
  return 0
end

function createObject()
  local img = xml_data.svg.g.image
  for i,v in ipairs(img) do
    textures[i] = {}
    --get name---------------
    textures[i].file = img[i]["@href"]
    --get size---------------
    textures[i].w = img[i]["@width"]
    textures[i].h = img[i]["@height"]
    --get position-----------
    textures[i].x = img[i]["@x"]
    textures[i].y = img[i]["@y"]
    --get UV
    local uvData = {getTextureData(textures[i].file)}
    textures[i].u = uvData[1]
    textures[i].v = uvData[2]
    textures[i].uSize = uvData[3]
    textures[i].vSize = uvData[4]
    --set flipU
  end
end

function loadXML()
  require "xml"
  xml = newParser()
  local file = assert(io.open("/rd/map_temple.svg", "r"))
  if not file then
    return "No SVG!"
  end
  local raw = file:read("*all")
  xml_data = assert(xml:ParseXmlText(raw))
  file:close()
  createObject()
  return textures[2].uSize
end

function loadJSON()
  local json = assert(require "json")
  local file = assert(io.open("/rd/data_map.json", "r"))
  if not file then
    return "No JSON Data"
  end
  --local file = assert(io.open("data_map.json", "r"))
  local raw = file:read("*all")
  file:close()
  data = json.decode(raw)
  return "JSON Decoded"
end

function getData()
  return t_string
end
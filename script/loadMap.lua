package.path = package.path .. ";cd/script/?.lua" .. ";pc/script/?.lua" .. ";../script/?.lua" .. ";/rd/?.lua"

sprite_data = {}
xml_data = {}
textures = {}
t_string = "super string!"
num = 4;
x_map, y_map = 0


function getTextureData(filename)
  local img_w = sprite_data.meta.size.w
  local img_h = sprite_data.meta.size.h
  for i,v in ipairs(sprite_data["frames"]) do
    local f = sprite_data["frames"][i]
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

--[[
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
--]]

function createObject(i)
  local img = xml_data.svg.g.image
  textures[i] = {}
  --get name---------------
  textures[i].file = img[i]["@href"]
  --get size---------------
  textures[i].w = img[i]["@width"]
  textures[i].h = img[i]["@height"]
  --get position-----------
  --translate = xml_data.svg.g["@transform"]
  textures[i].x = textures[i].w/2 + img[i]["@x"]
  textures[i].y = y_map - textures[i].h/2 - img[i]["@y"]
  --get UV
  local uvData = {getTextureData(textures[i].file)}
  textures[i].u = uvData[1]
  textures[i].v = uvData[2]
  textures[i].uSize = uvData[3]
  textures[i].vSize = uvData[4]
  textures[i].xScale = 1
  --set flipU
  if img[i]["@transform"] ~= nil then
    textures[i].x = (textures[i].x * -1)
    textures[i].xScale = -1
  end

  textures[i].desc = ""
  if img[i]["@desc"] ~= nil then
    textures[i].desc = img[i]["@desc"]
  end

  return textures[i].x, textures[i].y, textures[i].u, textures[i].v, textures[i].uSize, textures[i].vSize, textures[i].xScale, textures[i].desc,
  textures[i].file
end

function getMapInfo()
  x_map = xml_data.svg["@width"]
  y_map = xml_data.svg["@height"]
  local map_name = xml_data.svg.mapName
  local obj_num = #xml_data.svg.g.image
  return x_map, y_map, obj_num
end

function loadXML(filename)
  require "xml"
  xml = newParser()
  local file = assert(io.open(filename, "r"))
  if not file then
    return "No SVG!"
  end
  local raw = file:read("*all")
  xml_data = assert(xml:ParseXmlText(raw))
  file:close()
  return "SVG Loaded"
end

function loadJSON(filename)
  local json = assert(require "json")
  local file = assert(io.open(filename, "r"))
  if not file then
    return "No JSON sprite_data"
  end
  --local file = assert(io.open("data_map.json", "r"))
  local raw = file:read("*all")
  file:close()
  sprite_data = json.decode(raw)
  return "JSON Decoded"
end
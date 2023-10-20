// asagao/includes/tileset_layer.cpp


#include "stdafx.h"

#include "asagao.hpp"

#include "tileset_layer.hpp"


static TileUV get_tile_rule(const u8 mask);


TileSetLayer::TileSetLayer
(const str& name)
: name{name}
{}

str
TileSetLayer::get_new_number()
{
    static u16 i = 0;

    return std::to_string(++i);
}

void
TileSetLayer::paint
(const v2& tile)
{
    TilePos pair = std::make_pair(tile.x, tile.y);

    if (tiles.find(pair) == tiles.end())
    {
        tiles[pair] = get_uv(tile);

        // some tiles do not change with diagonal updates
        for (i8 y = -1; y <= 1; ++y)
        {
            for (i8 x = -1; x <= 1; ++x)
            {
                if (x || y)
                {
                    pair = std::make_pair(tile.x + x, tile.y + y);

                    if (tiles.find(pair) != tiles.end())
                        tiles[pair] = get_uv(tile + v2(x, y));
                }
            }
        }
    }
}

void
TileSetLayer::draw() const
{
    static GameObject obj
    (
        "----",
        v3(0.0f),
        0.0f,
        v3(1.0f),
        0.0f,
        true,
        1,
        {{0, 0}}
    );

    for (const auto& kv : tiles)
    {
        obj.position.x = kv.first.first  *  Asagao::Application.rect_size;
        obj.position.y = kv.first.second * -Asagao::Application.rect_size;

        obj.sprite_offsets[0].x = kv.second.x;
        obj.sprite_offsets[0].y = kv.second.y;

        Asagao::Renderer.draw(obj);
    }
}

TileUV
TileSetLayer::get_uv
(const v2& tile) const
{
    u8 power = 0;
    u8 mask  = 0;
    i8 x;

    // can be optimised
    for (i8 y = -1; y <= 1; ++y)
    {
        for (x = -1; x <= 1; ++x)
        {
            if (x || y)
            {
                if (tiles.find({tile.x + x, tile.y + y}) != tiles.end())
                    mask += std::pow(2, power);

                ++power;
            }
        }
    }

    return get_tile_rule(mask);
}


static TileUV
get_tile_rule
(const u8 mask)
{
    switch (mask)
    {
    case 208:
    case 209:
    case 212:
    case 213:
    case 240:
    case 241:
    case 244:
    case 245:
        return {0, 3};
    case 248:
    case 249:
    case 252:
    case 253:
        return {1, 3};
    case 104:
    case 105:
    case 108:
    case 109:
    case 232:
    case 233:
    case 236:
    case 237:
        return {2, 3};

    case 214:
    case 215:
    case 246:
    case 247:
        return {0, 2};
    case 255:
        return {1, 2};
    case 107:
    case 111:
    case 235:
    case 239:
        return {2, 2};

    case  22:
    case  23:
    case  54:
    case  55:
    case 150:
    case 151:
    case 182:
    case 183:
        return {0, 1};
    case  31:
    case  63:
    case 159:
    case 191:
        return {1, 1};
    case  11:
    case  15:
    case  43:
    case  47:
    case 139:
    case 143:
    case 171:
    case 175:
        return {2, 1};

    case   0:
    case   1:
    case   4:
    case   5:
    case  32:
    case  33:
    case  36:
    case  37:
    case 128:
    case 129:
    case 132:
    case 133:
    case 160:
    case 161:
    case 164:
    case 165:
        return {3, 1};
    case  16:
    case  17:
    case  20:
    case  21:
    case  48:
    case  49:
    case  52:
    case  53:
    case 144:
    case 145:
    case 148:
    case 149:
    case 176:
    case 177:
    case 180:
    case 181:
        return {2, 0};
    case   8:
    case   9:
    case  12:
    case  13:
    case  40:
    case  41:
    case  44:
    case  45:
    case 136:
    case 137:
    case 140:
    case 141:
    case 168:
    case 169:
    case 172:
    case 173:
        return {3, 0};
    case  64:
    case  65:
    case  68:
    case  69:
    case  96:
    case  97:
    case 100:
    case 101:
    case 192:
    case 193:
    case 196:
    case 197:
    case 224:
    case 225:
    case 228:
    case 229:
        return {4, 1};
    case   2:
    case   3:
    case   6:
    case   7:
    case  34:
    case  35:
    case  38:
    case  39:
    case 130:
    case 131:
    case 134:
    case 135:
    case 162:
    case 163:
    case 166:
    case 167:
        return {4, 0};

    case  24:
    case  25:
    case  28:
    case  29:
    case  56:
    case  57:
    case  60:
    case  61:
    case 152:
    case 153:
    case 189:
    case 184:
    case 185:
    case 156:
    case 188:
    case 157:
        return {0, 0};
    case  66:
    case  67:
    case  70:
    case  71:
    case  98:
    case  99:
    case 102:
    case 103:
    case 194:
    case 195:
    case 198:
    case 199:
    case 226:
    case 227:
    case 230:
    case 231:
        return {1, 0};

    case  80:
    case  81:
    case  84:
    case  85:
    case 112:
    case 113:
    case 116:
    case 117:
        return {3, 3};
    case  72:
    case  73:
    case  76:
    case  77:
    case 200:
    case 201:
    case 204:
    case 205:
        return {4, 3};
    case  18:
    case  19:
    case  50:
    case  51:
    case 146:
    case 147:
    case 178:
    case 179:
        return {3, 2};
    case  10:
    case  14:
    case  42:
    case  46:
    case 138:
    case 142:
    case 170:
    case 174:
        return {4, 2};

    case 120:
    case 121:
    case 124:
    case 125:
        return {5, 3};
    case 216:
    case 217:
    case 220:
    case 221:
        return {6, 3};
    case  27:
    case  59:
    case 155:
    case 187:
        return {5, 2};
    case  30:
    case  62:
    case 158:
    case 190:
        return {6, 2};

    case  86:
    case  87:
    case 118:
    case 119:
        return {5, 1};
    case  75:
    case  79:
    case 203:
    case 207:
        return {6, 1};
    case 210:
    case 211:
    case 242:
    case 243:
        return {5, 0};
    case 106:
    case 110:
    case 234:
    case 238:
        return {6, 0};

    case 122:
        return {7, 3};
    case 218:
        return {8, 3};
    case  91:
        return {7, 2};
    case  94:
        return {8, 2};

    case  82:
    case  83:
    case 114:
    case 115:
        return {7, 1};
    case  88:
    case  89:
    case  92:
    case  93:
        return {8, 1};
    case  26:
    case  58:
    case 154:
    case 186:
        return {7, 0};
    case  74:
    case  78:
    case 202:
    case 206:
        return {8, 0};

    case 127:
        return {11, 3};
    case 223:
        return {12, 3};
    case 251:
        return {11, 2};
    case 254:
        return {12, 2};

    case  90:
        return {10, 1};

    case  95:
        return {9, 3};
    case 222:
        return {10, 3};
    case 123:
        return {9, 2};
    case 250:
        return {10, 2};

    case 126:
        return {9, 1};
    case 219:
        return {9, 0};
    }

    // no need for a default case
}

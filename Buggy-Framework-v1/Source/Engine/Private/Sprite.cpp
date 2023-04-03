#include "../Public/Sprite.h"
#include "../Public/EngineSystemManager.h"

//👾 Alien Pet 4154
//👽 Alien 1550
//💩 Poop 1083
//🛸 UFO 462
//🚀 Rocket 2230
//☠️ Skull 1620
//👻 Ghost 1652
//🤬 Mad 571
//⚡️ Thunder 2987
//☄️ Fireball 3718
//💥 Bullet 2257
//🔥 Fire 1026
//🌈 Rainbow 3020
//🍜 Ramen 1557
//🍲 HotPot 2213
//🥄 Spoon 1634
//🍴 Fork and Knife 9622
//🎁 Gift 1051
//⚰️ Coffin 2188
//🪦 Headstone 4802
//🔞 18 161
//🏳️‍🌈 Rainbow Flag 7289
//🫀 Alien Boss Billy 12854

//🐌 Snail 1554
//🦋 Butterfly 4968
//🐛 Bug 609
//🐜 Ants 1093
//🐝 Honeybee 3736
//🐞 Ladybug 2967
//🦗 Cricket 2959
//🕷 Spider 2211
//🦂 Scorpion 3917
//🦟 Mosquito 4011
//🪲 Beetle 2181 
//🪳 Cockroach 4657
//🪱 Worm 1087 
//🦀 Crab 978 
//🦞 Lobster 3036 
//🐖 Pig 599

Sprite::Sprite()
{
}

Sprite::Sprite(string ModelName_Param)
{
  switch(StrToInt(ModelName_Param))
  {
    case 4154:
      SpriteModel = "👾";
      break;

    case 1550:
      SpriteModel = "👽";
      break;

    case 1083:
      SpriteModel = "💩";
      break;
    
    case 462:
      SpriteModel = "🛸";
      break;
    
    case 2230:
      SpriteModel = "🚀";
      break;
    
    case 1620:
      SpriteModel = "☠️";
      break;
    
    case 1652:
      SpriteModel = "👻";
      break;
    
    case 571:
      SpriteModel = "🤬";
      break;
    
    case 2987:
      SpriteModel = "⚡️";
      break;
    
    case 3718:
      SpriteModel = "☄️";
      break;
    
    case 2257:
      SpriteModel = "💥";
      break;
    
    case 1026:
      SpriteModel = "🔥";
      break;
    
    case 3020:
      SpriteModel = "🌈";
      break;
    
    case 1557:
      SpriteModel = "🍜";
      break;
    
    case 2213:
      SpriteModel = "🍲";
      break;
    
    case 1634:
      SpriteModel = "🥄";
      break;
    
    case 9622:
      SpriteModel = "🍴";
      break;
    
    case 1051:
      SpriteModel = "🎁";
      break;
    
    case 2188:
      SpriteModel = "⚰️";
      break;
    
    case 4802:
      SpriteModel = "🪦";
      break;
    
    case 161:
      SpriteModel = "🔞";
      break;
    
    case 7289:
      SpriteModel = "🏳️‍🌈";
      break;
    
    case 12854:
      SpriteModel = "🫀";
      break;

    case 1554:
      SpriteModel = "🐌";
      break;

    case 4968:
      SpriteModel = "🦋";
      break;

    case 609:
      SpriteModel = "🐛";
      break;

    case 1093:
      SpriteModel = "🐜";
      break;

    case 3736:
      SpriteModel = "🐝";
      break;

    case 2967:
      SpriteModel = "🐞";
      break;

    case 2959:
      SpriteModel = "🦗";
      break;

    case 2211:
      SpriteModel = "🕷";
      break;

    case 3917:
      SpriteModel = "🦂";
      break;

    case 4011:
      SpriteModel = "🦟";
      break;

    case 2181:
      SpriteModel = "🪲";
      break;

    case 4657:
      SpriteModel = "🪳";
      break;

    case 1087:
      SpriteModel = "🪱";
      break;

    case 978:
      SpriteModel = "🦀";
      break;

    case 3036:
      SpriteModel = "🦞";
      break;

    case 599:
      SpriteModel = "🐖";
      break;

    default :
      SpriteModel = "";
      break;
  }
}

void Sprite::SetSprite(string ModelName_Param)
{
  switch(StrToInt(ModelName_Param))
  {
    case 4154:
      SpriteModel = "👾";
      break;

    case 1550:
      SpriteModel = "👽";
      break;

    case 1083:
      SpriteModel = "💩";
      break;
    
    case 462:
      SpriteModel = "🛸";
      break;
    
    case 2230:
      SpriteModel = "🚀";
      break;
    
    case 1620:
      SpriteModel = "☠️";
      break;
    
    case 1652:
      SpriteModel = "👻";
      break;
    
    case 571:
      SpriteModel = "🤬";
      break;
    
    case 2987:
      SpriteModel = "⚡️";
      break;
    
    case 3718:
      SpriteModel = "☄️";
      break;
    
    case 2257:
      SpriteModel = "💥";
      break;
    
    case 1026:
      SpriteModel = "🔥";
      break;
    
    case 3020:
      SpriteModel = "🌈";
      break;
    
    case 1557:
      SpriteModel = "🍜";
      break;
    
    case 2213:
      SpriteModel = "🍲";
      break;
    
    case 1634:
      SpriteModel = "🥄";
      break;
    
    case 9622:
      SpriteModel = "🍴";
      break;
    
    case 1051:
      SpriteModel = "🎁";
      break;
    
    case 2188:
      SpriteModel = "⚰️";
      break;
    
    case 4802:
      SpriteModel = "🪦";
      break;
    
    case 161:
      SpriteModel = "🔞";
      break;
    
    case 7289:
      SpriteModel = "🏳️‍🌈";
      break;
    
    case 12854:
      SpriteModel = "🫀";
      break;

    case 1554:
      SpriteModel = "🐌";
      break;

    case 4968:
      SpriteModel = "🦋";
      break;

    case 609:
      SpriteModel = "🐛";
      break;

    case 1093:
      SpriteModel = "🐜";
      break;

    case 3736:
      SpriteModel = "🐝";
      break;

    case 2967:
      SpriteModel = "🐞";
      break;

    case 2959:
      SpriteModel = "🦗";
      break;

    case 2211:
      SpriteModel = "🕷";
      break;

    case 3917:
      SpriteModel = "🦂";
      break;

    case 4011:
      SpriteModel = "🦟";
      break;

    case 2181:
      SpriteModel = "🪲";
      break;

    case 4657:
      SpriteModel = "🪳";
      break;

    case 1087:
      SpriteModel = "🪱";
      break;

    case 978:
      SpriteModel = "🦀";
      break;

    case 3036:
      SpriteModel = "🦞";
      break;

    case 599:
      SpriteModel = "🐖";
      break;

    default :
      SpriteModel = "";
      break;
  }
}

string Sprite::GetSprite()
{
  return this->SpriteModel;
}

Sprite::~Sprite()
{
}
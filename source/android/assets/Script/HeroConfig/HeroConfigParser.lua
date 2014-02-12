require("Script/HeroConfig/hero_config")

function HeroConfigParser_GetOneHeroAnimID(typeId)
	local item = Heros[typeId]
	if item == nil then
		return 0
	else
		return tonumber(item.AnimRcs)
	end
end

function HeroConfigParser_GetSkillID(typeId)
	local item = Heros[typeId]
	if item == nil then
		return 0
	else
		return tonumber(item.SkillID)
	end
end
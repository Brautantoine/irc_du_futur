function onEnable()
	print("enable script Test")
end

function onDisable()
end

function onMessage(EventMessage)
	print("[TEST LUA] x=" .. x)
	--print("[TEST LUA] message " .. EventMessage:getMessage())
	--EventMessage:setMessage("TSTELUALAA")
	--print("[TEST LUA] username" .. EventMessage:getClient():getUsername())
	return false
end
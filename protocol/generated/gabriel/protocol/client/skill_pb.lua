-- Generated By protoc-gen-lua Do not Edit
local protobuf = require "protobuf"
module('gabriel/protocol/client/skill_pb')


local SKILL_MSG_ID = protobuf.EnumDescriptor();
local SKILL_MSG_ID_CREATE_SKILL_ENUM = protobuf.EnumValueDescriptor();

SKILL_MSG_ID_CREATE_SKILL_ENUM.name = "CREATE_SKILL"
SKILL_MSG_ID_CREATE_SKILL_ENUM.index = 0
SKILL_MSG_ID_CREATE_SKILL_ENUM.number = 1
SKILL_MSG_ID.name = "SKILL_MSG_ID"
SKILL_MSG_ID.full_name = ".gabriel.protocol.client.SKILL_MSG_ID"
SKILL_MSG_ID.values = {SKILL_MSG_ID_CREATE_SKILL_ENUM}

CREATE_SKILL = 1

@echo
	
cls

set PROJ_DIR=%cd%
set ONLINE_PROTO_DIR=%PROJ_DIR%\..\proto

set NETWORK_DIR=%PROJ_DIR%\Classes\Engine\NetWork


cd %PROJ_DIR%
copy %ONLINE_PROTO_DIR%\*.proto %NETWORK_DIR%\proto\*.proto
rem copy %NETWORK_DIR%\proto\*.proto %SERVER_DIR%\proto\*.proto

%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_core.proto 
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_basic.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_battle.proto  
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\errcode.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\db.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\cs_config.proto
%PROJ_DIR%\tools\ProtoBuf\protoc.exe -I=%NETWORK_DIR%\proto --cpp_out=%NETWORK_DIR% %NETWORK_DIR%\proto\head.proto
echo copy cc file to server dir
copy %NETWORK_DIR%\*.pb.* %PROJ_DIR%\..\server\online\trunk\src\proto



cd %PROJ_DIR%
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

struct SDKConfig
{
	/** The product id for the running application, found on the dev portal */
	static constexpr char ProductId[] = "250c56433e4f4698abe63daeb782359f";

	/** The sandbox id for the running application, found on the dev portal */
	static constexpr char SandboxId[] = "0406d6b1a6394c7f8209a72efd8ced3c";

	/** The deployment id for the running application, found on the dev portal */
	static constexpr char DeploymentId[] = "4077af9fee6a480daa33773d1b3260a8";

	/** Client id of the service permissions entry, found on the dev portal */
	static constexpr char ClientCredentialsId[] = "xyza78914fNIgK9VP9atsd6FaUoMzxo9";

	/** Client secret for accessing the set of permissions, found on the dev portal */
	static constexpr char ClientCredentialsSecret[] = "CsmN9CqsTnYO88AuN+qwsjvk61tResMQX0tVM6v2LmQ";

	/** Game name */
	static constexpr char GameName[] = "StubGame";

	/** Encryption key */
	static constexpr char EncryptionKey[] = "1111111111111111111111111111111111111111111111111111111111111111";

	/** Credential name in the DevAuthTool */
	static constexpr char CredentialName[] = "ThatJMac-credential";

	/** Host name in the DevAuthTool */
	static constexpr char Port[] = "localhost:6547";
};

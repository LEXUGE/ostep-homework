{
  description = "OSTEP Homeworks";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    utils.url = "github:numtide/flake-utils";
    git-hooks = {
      url = "github:cachix/git-hooks.nix";
      inputs.nixpkgs.follows = "nixpkgs";
    };
  };
  outputs =
    {
      self,
      nixpkgs,
      utils,
      git-hooks,
      ...
    }:
    with nixpkgs.lib;
    let
      pkgs =
        system:
        import nixpkgs {
          system = "${system}";
          config.allowUnfree = true;
        };
    in
    utils.lib.eachSystem
      (with utils.lib.system; [
        x86_64-linux
      ])
      (system: rec {
        checks = {
          pre-commit-check = git-hooks.lib.${system}.run {
            src = ./.;
            hooks = {
              nixfmt.enable = true;
              clang-format.enable = true;
            };
          };
        };

        devShells.default =
          with (pkgs system);
          mkShell {
            inherit (self.checks.${system}.pre-commit-check) shellHook;
            nativeBuildInputs = [
              uv
              gcc
              clang-tools
            ];
          };
      });
}

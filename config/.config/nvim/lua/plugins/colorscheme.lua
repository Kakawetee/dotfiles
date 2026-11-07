return {
    "catppuccin/nvim",
    name = "catppuccin",
    lazy = false,
    priority = 1000,          -- se carga antes que el resto
    opts = {
        flavour = "mocha",
        transparent_background = true,
        integrations = {
            treesitter = true,
            -- aquí irán telescope, gitsigns, etc. cuando los instales
        },
    },
    config = function(_, opts)
        require("catppuccin").setup(opts)
        vim.cmd.colorscheme("catppuccin")
    end,
}

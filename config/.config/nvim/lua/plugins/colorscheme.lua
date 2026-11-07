return {
    "catppuccin/nvim",
    name = "catppuccin",
    lazy = false,
    priority = 1000,          -- se carga antes que el resto
    opts = {
        flavour = "mocha",
        transparent_background = false, -- como kitty esta sin tunear por ahora se deja asi
        color_overrides = { mocha = { base = "#0a1c2c", mantle = "#040b10", crust = "#040b10" } },
        -- Por ahora color_override hasta que programe la terminal de los cuyons
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

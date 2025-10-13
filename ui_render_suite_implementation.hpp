#ifndef UI_RENDER_SUITE_IMPLEMENTATION_HPP
#define UI_RENDER_SUITE_IMPLEMENTATION_HPP

#include "sbpt_generated_includes.hpp"

class UIRenderSuiteImpl : public IUIRenderSuite {
  public:
    Batcher &batcher;

    explicit UIRenderSuiteImpl(Batcher &batcher) : batcher(batcher) {}

    void render_colored_box(const UIRect &cb) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            cb.ivpsc.id, cb.ivpsc.indices, cb.ivpsc.xyz_positions, cb.ivpsc.rgb_colors,
            cb.modified_signal.has_just_changed());
    }

    void render_text_box(const UITextBox &tb) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            tb.text_drawing_ivpsc.id, tb.text_drawing_ivpsc.indices, tb.text_drawing_ivpsc.xyz_positions,
            tb.text_drawing_ivpsc.rgb_colors, tb.modified_signal.has_just_changed());

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            tb.background_ivpsc.id, tb.background_ivpsc.indices, tb.background_ivpsc.xyz_positions,
            tb.background_ivpsc.rgb_colors, tb.modified_signal.has_just_changed());
    }

    void render_clickable_text_box(const UIClickableTextBox &cr) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            cr.text_drawing_ivpsc.id, cr.text_drawing_ivpsc.indices, cr.text_drawing_ivpsc.xyz_positions,
            cr.text_drawing_ivpsc.rgb_colors);

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            cr.ivpsc.id, cr.ivpsc.indices, cr.ivpsc.xyz_positions, cr.ivpsc.rgb_colors,
            cr.modified_signal.has_just_changed());
    }

    void render_input_box(const UIInputBox &ib) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            ib.text_drawing_ivpsc.id, ib.text_drawing_ivpsc.indices, ib.text_drawing_ivpsc.xyz_positions,
            ib.text_drawing_ivpsc.rgb_colors, ib.modified_signal.has_just_changed());

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            ib.background_ivpsc.id, ib.background_ivpsc.indices, ib.background_ivpsc.xyz_positions,
            ib.background_ivpsc.rgb_colors, ib.modified_signal.has_just_changed());
    }

    void render_dropdown(const UIDropdown &dd) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            dd.dropdown_text_ivpsc.id, dd.dropdown_text_ivpsc.indices, dd.dropdown_text_ivpsc.xyz_positions,
            dd.dropdown_text_ivpsc.rgb_colors, dd.modified_signal.has_just_changed());

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            dd.dropdown_background.id, dd.dropdown_background.indices, dd.dropdown_background.xyz_positions,
            dd.dropdown_background.rgb_colors, dd.modified_signal.has_just_changed());
    }

    /**
     * @pre assumes that the absolute_position_with_colored_vertex_shader_batcher exists
     */
    void render_dropdown_option(const UIDropdownOption &udo) override {

        auto text_ivpsc = udo.text_ivpsc;
        auto ivpsc = udo.background_ivpsc;

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            text_ivpsc.id, text_ivpsc.indices, text_ivpsc.xyz_positions, text_ivpsc.rgb_colors,
            udo.modified_signal.has_just_changed());

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(
            ivpsc.id, ivpsc.indices, ivpsc.xyz_positions, ivpsc.rgb_colors, udo.modified_signal.has_just_changed());
    }
};

#endif // UI_RENDER_SUITE_IMPLEMENTATION_HPP

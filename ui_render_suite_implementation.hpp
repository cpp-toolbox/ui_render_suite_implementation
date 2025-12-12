#ifndef UI_RENDER_SUITE_IMPLEMENTATION_HPP
#define UI_RENDER_SUITE_IMPLEMENTATION_HPP

#include "sbpt_generated_includes.hpp"

/**
 * @class UIRenderSuiteImpl
 * @brief Concrete implementation of the IUIRenderSuite interface responsible for rendering UI components.
 *
 * This class provides rendering logic for various UI element types such as colored boxes, text boxes,
 * clickable text boxes, input boxes, and dropdowns. It uses a shared Batcher instance to enqueue draw calls
 * into a specific vertex shader batcher, typically one using absolute positioning and per-vertex coloring.
 *
 * @note All rendering operations assume that the `absolute_position_with_colored_vertex_shader_batcher`
 *       inside the Batcher is properly initialized and bound to the correct rendering pipeline.
 *
 * @note I need to implement some sort of deletion thing in here I think because externally I am doing things like this,
 which I don't like because it requires that you have knowledge of multiple systems to properly delete a single ui. In
 order to fix the whole way ui is handled should be re-thought and replanned most likely, probably using signal emitters
 might help or something like this.
 *
 * @code
        for (auto id_of_dynamic_leaderboard_textbox : ids_of_dynamic_leaderboard_textboxes) {
            UITextBox *tb = leaderboard.get_textbox(id_of_dynamic_leaderboard_textbox);

            if (tb) {
                tbx_engine.batcher.absolute_position_with_colored_vertex_shader_batcher.delete_object(
                    tb->background_ivpsc.id);
                tbx_engine.batcher.absolute_position_with_colored_vertex_shader_batcher.delete_object(
                    tb->text_drawing_ivpsc.id);
                leaderboard.remove_textbox(
                    id_of_dynamic_leaderboard_textbox); // WARN: after this line tb is probably garbage
            }
        }
 * @endcode
 */
class UIRenderSuiteImpl : public IUIRenderSuite {
  public:
    /**
     * @brief Reference to the shared Batcher used for managing batched draw calls.
     */
    Batcher &batcher;

    /**
     * @brief Constructs a new UIRenderSuiteImpl with the provided Batcher.
     *
     * @param batcher Reference to the Batcher that will handle vertex submission.
     */
    explicit UIRenderSuiteImpl(Batcher &batcher) : batcher(batcher) {}

    /**
     * @brief Renders a colored rectangular UI element.
     *
     * @param cb The UIRect object containing vertex data and color information.
     *
     * @details This method queues a draw command for a simple colored rectangle using
     *          the absolute-position colored vertex shader batcher.
     */
    void render_colored_box(UIRect &cb) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(cb.ivpsc);
    }

    /**
     * @brief Renders a text box including both its text and background.
     *
     * @param tb The UITextBox object containing both text and background geometry.
     *
     * @details Two draw calls are queued: one for the text and another for the background.
     *          Each part uses separate IndexedVertexPositionColor structures.
     */
    void render_text_box(UITextBox &tb) override {

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(tb.text_drawing_ivpsc);
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(tb.background_ivpsc);
    }

    /**
     * @brief Renders a clickable text box element.
     *
     * @param cr The UIClickableTextBox object representing the clickable text box.
     *
     * @details This function queues draw calls for both the text and background portions.
     *          The clickable area is typically visually distinct from a standard text box.
     */
    void render_clickable_text_box(UIClickableTextBox &cr) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(cr.text_drawing_ivpsc);
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(cr.ivpsc);
    }

    /**
     * @brief Renders a user input box element.
     *
     * @param ib The UIInputBox object containing text and background data.
     *
     * @details The input box is composed of text (the current user input or placeholder)
     *          and a background. Both are drawn as separate geometry.
     */
    void render_input_box(UIInputBox &ib) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(ib.text_drawing_ivpsc);
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(ib.background_ivpsc);
    }

    /**
     * @brief Renders a dropdown element including its text and background.
     *
     * @param dd The UIDropdown object representing the dropdown.
     *
     * @details The dropdown consists of the main visible area (background) and
     *          its currently selected text. Both are rendered as separate draw calls.
     */
    void render_dropdown(UIDropdown &dd) override {

        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(dd.dropdown_text_ivpsc);
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(dd.dropdown_background);
    }

    /**
     * @brief Renders an individual dropdown option.
     *
     * @param udo The UIDropdownOption representing a single selectable option.
     *
     * @pre Assumes that the `absolute_position_with_colored_vertex_shader_batcher`
     *      exists and is properly initialized.
     *
     * @details Each dropdown option is composed of background geometry and text.
     *          Both are rendered as individual draw calls to allow per-option
     *          color and layout customization.
     */
    void render_dropdown_option(UIDropdownOption &udo) override {
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(udo.text_ivpsc);
        batcher.absolute_position_with_colored_vertex_shader_batcher.queue_draw(udo.background_ivpsc);
    }
};

#endif // UI_RENDER_SUITE_IMPLEMENTATION_HPP

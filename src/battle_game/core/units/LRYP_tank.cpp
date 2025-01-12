#include "LRYP_tank.h"

#include "battle_game/core/bullets/bullets.h"
#include "battle_game/core/game_core.h"
#include "battle_game/graphics/graphics.h"

namespace battle_game::unit {

namespace {
uint32_t tank_body_model_index = 0xffffffffu;
uint32_t tank_turret_model_index = 0xffffffffu;
}

LRYPTank::LRYPTank(GameCore *game_core, uint32_t id, uint32_t player_id)
    : Unit(game_core, id, player_id) {
  if (!~tank_body_model_index) {
    auto mgr = AssetsManager::GetInstance();
    {
      tank_body_model_index = mgr->RegisterModel(
          {
            {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.4f, 0.5f, 0.4f, 1.0f}},  // 中心
            {{-1.0f, -0.8f}, {0.0f, 0.0f}, {0.2f, 0.3f, 0.2f, 1.0f}}, // 左下
            {{1.0f, -0.8f}, {0.0f, 0.0f}, {0.2f, 0.3f, 0.2f, 1.0f}},  // 右下
            {{-1.0f, 0.8f}, {0.0f, 0.0f}, {0.2f, 0.3f, 0.2f, 1.0f}},  // 左上
            {{1.0f, 0.8f}, {0.0f, 0.0f}, {0.2f, 0.3f, 0.2f, 1.0f}},   // 右上
            {{-0.8f, -1.2f}, {0.0f, 0.0f}, {0.3f, 0.4f, 0.3f, 1.0f}}, // 左下
            {{0.8f, -1.2f}, {0.0f, 0.0f}, {0.3f, 0.4f, 0.3f, 1.0f}},  // 右下
            {{-0.8f, 1.2f}, {0.0f, 0.0f}, {0.3f, 0.4f, 0.3f, 1.0f}},  // 左上
            {{0.8f, 1.2f}, {0.0f, 0.0f}, {0.3f, 0.4f, 0.3f, 1.0f}},   // 右上
            {{0.0f, -1.4f}, {0.0f, 0.0f}, {0.5f, 0.6f, 0.5f, 1.0f}},  // 底中
            {{0.0f, 1.8f}, {0.0f, 0.0f}, {0.5f, 0.6f, 0.5f, 1.0f}},   // 顶中
          },
          {0, 1, 2, 0, 2, 4, 0, 4, 3, 0, 3, 1, 1, 5, 6, 1, 6, 2, 3, 4, 7, 4, 7, 8, 1, 5, 8, 7, 8, 10, 7, 8, 9});
    }

    {
      tank_turret_model_index =
          mgr->RegisterModel({
            {{0.0f, 0.0f}, {0.0f, 0.0f}, {0.4f, 0.4f, 0.4f, 1.0f}},  // 中心
            {{-0.4f, -0.6f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}}, // 左下
            {{-0.3f, -0.7f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}}, // 左下
            {{0.3f, -0.7f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},  // 右下
            {{0.4f, -0.6f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},  // 右下
            {{0.4f, 0.6f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},   // 右上
            {{0.3f, 0.7f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},   // 右上
            {{-0.3f, 0.7f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},  // 左上
            {{-0.4f, 0.6f}, {0.0f, 0.0f}, {0.3f, 0.3f, 0.3f, 1.0f}},  // 左上
            {{-0.1f, 0.0f}, {0.0f, 0.0f}, {0.4f, 0.4f, 0.4f, 1.0f}},   // 炮管根部
            {{0.1f, 0.0f}, {0.0f, 0.0f}, {0.4f, 0.4f, 0.4f, 1.0f}},   // 炮管根部
            {{0.1f, 1.9f}, {0.0f, 0.0f}, {0.2f, 0.2f, 0.2f, 1.0f}},   // 炮管顶部
            {{0.05f, 2.0f}, {0.0f, 0.0f}, {0.2f, 0.2f, 0.2f, 1.0f}},   // 炮管顶部
            {{-0.05f, 2.0f}, {0.0f, 0.0f}, {0.2f, 0.2f, 0.2f, 1.0f}},   // 炮管顶部
            {{-0.1f, 1.9f}, {0.0f, 0.0f}, {0.2f, 0.2f, 0.2f, 1.0f}},   // 炮管顶部

          }, {0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 7, 0, 7, 8, 0, 8, 1, 9, 10, 11, 9, 11, 12, 9, 12, 13, 9, 13, 14});
    }
  }
}

void LRYPTank::Render() {
  battle_game::SetTransformation(position_, rotation_);
  battle_game::SetTexture(0);
  battle_game::SetColor(game_core_->GetPlayerColor(player_id_));
  battle_game::DrawModel(tank_body_model_index);
  battle_game::SetRotation(turret_rotation_);
  battle_game::DrawModel(tank_turret_model_index);
}

void LRYPTank::Update() {
  TankMove(1.5f, glm::radians(90.0f));
  TurretRotate();
  Fire();
}

void LRYPTank::TankMove(float move_speed, float rotate_angular_speed) {
  auto player = game_core_->GetPlayer(player_id_);
  if (player) {
    auto &input_data = player->GetInputData();
    glm::vec2 offset{0.0f};
    if (input_data.key_down[GLFW_KEY_W]) {
      offset.y += 1.0f;
    }
    if (input_data.key_down[GLFW_KEY_S]) {
      offset.y -= 1.0f;
    }
    if (input_data.key_down[GLFW_KEY_A]) {
      offset.x -= 1.0f;
    }
    if (input_data.key_down[GLFW_KEY_D]) {
      offset.x += 1.0f;
    }
    float speed = move_speed * GetSpeedScale();
    offset *= kSecondPerTick * speed;
    auto new_position =
        position_ + glm::vec2{glm::rotate(glm::mat4{1.0f}, rotation_,
                                          glm::vec3{0.0f, 0.0f, 1.0f}) *
                              glm::vec4{offset, 0.0f, 0.0f}};
    if (!game_core_->IsBlockedByObstacles(new_position)) {
      game_core_->PushEventMoveUnit(id_, new_position);
    }
    float rotation_offset = 0.0f;
    if (input_data.key_down[GLFW_KEY_Q]) {
      rotation_offset += 1.0f;
    }
    if (input_data.key_down[GLFW_KEY_E]) {
      rotation_offset -= 1.0f;
    }
    rotation_offset *= kSecondPerTick * rotate_angular_speed * GetSpeedScale();
    game_core_->PushEventRotateUnit(id_, rotation_ + rotation_offset);
  }
}

void LRYPTank::TurretRotate() {
  auto player = game_core_->GetPlayer(player_id_);
  if (player) {
    auto &input_data = player->GetInputData();
    auto diff = input_data.mouse_cursor_position - position_;
    if (glm::length(diff) < 1e-4) {
      turret_rotation_ = rotation_;
    } else {
      turret_rotation_ = std::atan2(diff.y, diff.x) - glm::radians(90.0f);
    }
  }
}

void LRYPTank::Fire() {
  if (fire_count_down_ == 0) {
    auto player = game_core_->GetPlayer(player_id_);
    if (player) {
      auto &input_data = player->GetInputData();
      if (input_data.mouse_button_down[GLFW_MOUSE_BUTTON_LEFT]) {
        auto velocity = Rotate(glm::vec2{0.0f, 20.0f}, turret_rotation_);
        GenerateBullet<bullet::CannonBall>(
            position_ + Rotate({0.0f, 2.0f}, turret_rotation_),
            turret_rotation_, GetDamageScale(), velocity);
        fire_count_down_ = kTickPerSecond / 2;
      } else if (input_data.mouse_button_down[GLFW_MOUSE_BUTTON_RIGHT]) {
        fire_count_down_ = kTickPerSecond;
        multishooting_ = 3;
      }
    }
  }
  if (multishooting_ && (kTickPerSecond - fire_count_down_) % (kTickPerSecond / 10) == 0) {
    auto player = game_core_->GetPlayer(player_id_);
    if (player) {
      auto velocity = Rotate(glm::vec2{0.0f, 7.0f}, turret_rotation_);
      GenerateBullet<bullet::CannonBall>(
          position_ + Rotate({0.0f, 2.0f}, turret_rotation_),
          turret_rotation_, GetDamageScale() * 0.8f, velocity);
      multishooting_ --;
    }
  }
  if (fire_count_down_) {
    fire_count_down_--;
  }
}

bool LRYPTank::IsHit(glm::vec2 position) const {
  position = WorldToLocal(position);
  return position.x > -1.0f && position.x < 1.0f && position.y > -1.4f && position.y < 1.8f && 
         -0.4f * position.x + 0.2f * position.y < 0.56f && 0.4f * position.x + 0.2f * position.y < 0.56f && 
         -0.4f * position.x + 0.2f * position.y > -0.56f && 0.4f * position.x + 0.2f * position.y > -0.56f && 
         -0.6f * position.x + 0.8f * position.y < 1.44f && 0.6f * position.x + 0.8f * position.y < 1.44f && 
         -0.2f * position.x + 0.8f * position.y > -1.12f && 0.2f * position.x + 0.8f * position.y > -1.12f;
}

const char *LRYPTank::UnitName() const {
  return "Massive LRYPTank";
}

const char *LRYPTank::Author() const {
  return "LRYP";
}
}
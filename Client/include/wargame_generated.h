// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_WARGAME_WARGAME_FB_H_
#define FLATBUFFERS_GENERATED_WARGAME_WARGAME_FB_H_

#include <flatbuffers/flatbuffers.h>

namespace WarGame {
	namespace fb {

		struct s_vector2u;

		struct playerBase;

		struct players;

		struct requestId;

		struct bullet;

		struct deleteBullet;

		struct bullets;

		MANUALLY_ALIGNED_STRUCT(8) s_vector2u FLATBUFFERS_FINAL_CLASS {
		private:
			uint64_t x_;
			uint64_t y_;

		public:
			s_vector2u() {
				memset(this, 0, sizeof(s_vector2u));
			}
			s_vector2u(uint64_t _x, uint64_t _y)
				: x_(flatbuffers::EndianScalar(_x)),
				y_(flatbuffers::EndianScalar(_y)) {
			}
			uint64_t x() const {
				return flatbuffers::EndianScalar(x_);
			}
			uint64_t y() const {
				return flatbuffers::EndianScalar(y_);
			}
		};
		STRUCT_END(s_vector2u, 16);

		struct playerBase FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_NAME = 4,
				VT_ID = 6,
				VT_HEALTH = 8,
				VT_AMMO = 10,
				VT_ORIENTATION = 12,
				VT_STATE = 14,
				VT_POS = 16
			};
			const flatbuffers::String *name() const {
				return GetPointer<const flatbuffers::String *>(VT_NAME);
			}
			uint16_t id() const {
				return GetField<uint16_t>(VT_ID, 0);
			}
			uint16_t health() const {
				return GetField<uint16_t>(VT_HEALTH, 0);
			}
			uint16_t ammo() const {
				return GetField<uint16_t>(VT_AMMO, 0);
			}
			uint16_t orientation() const {
				return GetField<uint16_t>(VT_ORIENTATION, 0);
			}
			uint16_t state() const {
				return GetField<uint16_t>(VT_STATE, 0);
			}
			const s_vector2u *pos() const {
				return GetStruct<const s_vector2u *>(VT_POS);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyOffset(verifier, VT_NAME) &&
					verifier.Verify(name()) &&
					VerifyField<uint16_t>(verifier, VT_ID) &&
					VerifyField<uint16_t>(verifier, VT_HEALTH) &&
					VerifyField<uint16_t>(verifier, VT_AMMO) &&
					VerifyField<uint16_t>(verifier, VT_ORIENTATION) &&
					VerifyField<uint16_t>(verifier, VT_STATE) &&
					VerifyField<s_vector2u>(verifier, VT_POS) &&
					verifier.EndTable();
			}
		};

		struct playerBaseBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_name(flatbuffers::Offset<flatbuffers::String> name) {
				fbb_.AddOffset(playerBase::VT_NAME, name);
			}
			void add_id(uint16_t id) {
				fbb_.AddElement<uint16_t>(playerBase::VT_ID, id, 0);
			}
			void add_health(uint16_t health) {
				fbb_.AddElement<uint16_t>(playerBase::VT_HEALTH, health, 0);
			}
			void add_ammo(uint16_t ammo) {
				fbb_.AddElement<uint16_t>(playerBase::VT_AMMO, ammo, 0);
			}
			void add_orientation(uint16_t orientation) {
				fbb_.AddElement<uint16_t>(playerBase::VT_ORIENTATION, orientation, 0);
			}
			void add_state(uint16_t state) {
				fbb_.AddElement<uint16_t>(playerBase::VT_STATE, state, 0);
			}
			void add_pos(const s_vector2u *pos) {
				fbb_.AddStruct(playerBase::VT_POS, pos);
			}
			explicit playerBaseBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			playerBaseBuilder &operator=(const playerBaseBuilder &);
			flatbuffers::Offset<playerBase> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<playerBase>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<playerBase> CreateplayerBase(
			flatbuffers::FlatBufferBuilder &_fbb,
			flatbuffers::Offset<flatbuffers::String> name = 0,
			uint16_t id = 0,
			uint16_t health = 0,
			uint16_t ammo = 0,
			uint16_t orientation = 0,
			uint16_t state = 0,
			const s_vector2u *pos = 0) {
			playerBaseBuilder builder_(_fbb);
			builder_.add_pos(pos);
			builder_.add_name(name);
			builder_.add_state(state);
			builder_.add_orientation(orientation);
			builder_.add_ammo(ammo);
			builder_.add_health(health);
			builder_.add_id(id);
			return builder_.Finish();
		}

		inline flatbuffers::Offset<playerBase> CreateplayerBaseDirect(
			flatbuffers::FlatBufferBuilder &_fbb,
			const char *name = nullptr,
			uint16_t id = 0,
			uint16_t health = 0,
			uint16_t ammo = 0,
			uint16_t orientation = 0,
			uint16_t state = 0,
			const s_vector2u *pos = 0) {
			return WarGame::fb::CreateplayerBase(
				_fbb,
				name ? _fbb.CreateString(name) : 0,
				id,
				health,
				ammo,
				orientation,
				state,
				pos);
		}

		struct players FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_VECPLAYERS = 4
			};
			const flatbuffers::Vector<flatbuffers::Offset<playerBase>> *vecPlayers() const {
				return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<playerBase>> *>(VT_VECPLAYERS);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyOffset(verifier, VT_VECPLAYERS) &&
					verifier.Verify(vecPlayers()) &&
					verifier.VerifyVectorOfTables(vecPlayers()) &&
					verifier.EndTable();
			}
		};

		struct playersBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_vecPlayers(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<playerBase>>> vecPlayers) {
				fbb_.AddOffset(players::VT_VECPLAYERS, vecPlayers);
			}
			explicit playersBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			playersBuilder &operator=(const playersBuilder &);
			flatbuffers::Offset<players> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<players>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<players> Createplayers(
			flatbuffers::FlatBufferBuilder &_fbb,
			flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<playerBase>>> vecPlayers = 0) {
			playersBuilder builder_(_fbb);
			builder_.add_vecPlayers(vecPlayers);
			return builder_.Finish();
		}

		inline flatbuffers::Offset<players> CreateplayersDirect(
			flatbuffers::FlatBufferBuilder &_fbb,
			const std::vector<flatbuffers::Offset<playerBase>> *vecPlayers = nullptr) {
			return WarGame::fb::Createplayers(
				_fbb,
				vecPlayers ? _fbb.CreateVector<flatbuffers::Offset<playerBase>>(*vecPlayers) : 0);
		}

		struct requestId FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_NEWID = 4,
				VT_NAME = 6,
				VT_NEWX = 8,
				VT_NEWY = 10
			};
			int16_t newId() const {
				return GetField<int16_t>(VT_NEWID, 0);
			}
			const flatbuffers::String *name() const {
				return GetPointer<const flatbuffers::String *>(VT_NAME);
			}
			uint16_t newX() const {
				return GetField<uint16_t>(VT_NEWX, 0);
			}
			uint16_t newY() const {
				return GetField<uint16_t>(VT_NEWY, 0);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyField<int16_t>(verifier, VT_NEWID) &&
					VerifyOffset(verifier, VT_NAME) &&
					verifier.Verify(name()) &&
					VerifyField<uint16_t>(verifier, VT_NEWX) &&
					VerifyField<uint16_t>(verifier, VT_NEWY) &&
					verifier.EndTable();
			}
		};

		struct requestIdBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_newId(int16_t newId) {
				fbb_.AddElement<int16_t>(requestId::VT_NEWID, newId, 0);
			}
			void add_name(flatbuffers::Offset<flatbuffers::String> name) {
				fbb_.AddOffset(requestId::VT_NAME, name);
			}
			void add_newX(uint16_t newX) {
				fbb_.AddElement<uint16_t>(requestId::VT_NEWX, newX, 0);
			}
			void add_newY(uint16_t newY) {
				fbb_.AddElement<uint16_t>(requestId::VT_NEWY, newY, 0);
			}
			explicit requestIdBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			requestIdBuilder &operator=(const requestIdBuilder &);
			flatbuffers::Offset<requestId> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<requestId>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<requestId> CreaterequestId(
			flatbuffers::FlatBufferBuilder &_fbb,
			int16_t newId = 0,
			flatbuffers::Offset<flatbuffers::String> name = 0,
			uint16_t newX = 0,
			uint16_t newY = 0) {
			requestIdBuilder builder_(_fbb);
			builder_.add_name(name);
			builder_.add_newY(newY);
			builder_.add_newX(newX);
			builder_.add_newId(newId);
			return builder_.Finish();
		}

		inline flatbuffers::Offset<requestId> CreaterequestIdDirect(
			flatbuffers::FlatBufferBuilder &_fbb,
			int16_t newId = 0,
			const char *name = nullptr,
			uint16_t newX = 0,
			uint16_t newY = 0) {
			return WarGame::fb::CreaterequestId(
				_fbb,
				newId,
				name ? _fbb.CreateString(name) : 0,
				newX,
				newY);
		}

		struct bullet FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_ID = 4,
				VT_OWNERID = 6,
				VT_SRC_X = 8,
				VT_SRC_Y = 10,
				VT_DST_X = 12,
				VT_DST_Y = 14,
				VT_W = 16,
				VT_H = 18
			};
			uint16_t id() const {
				return GetField<uint16_t>(VT_ID, 0);
			}
			uint16_t ownerId() const {
				return GetField<uint16_t>(VT_OWNERID, 0);
			}
			uint16_t src_x() const {
				return GetField<uint16_t>(VT_SRC_X, 0);
			}
			uint16_t src_y() const {
				return GetField<uint16_t>(VT_SRC_Y, 0);
			}
			uint16_t dst_x() const {
				return GetField<uint16_t>(VT_DST_X, 0);
			}
			uint16_t dst_y() const {
				return GetField<uint16_t>(VT_DST_Y, 0);
			}
			uint16_t w() const {
				return GetField<uint16_t>(VT_W, 0);
			}
			uint16_t h() const {
				return GetField<uint16_t>(VT_H, 0);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyField<uint16_t>(verifier, VT_ID) &&
					VerifyField<uint16_t>(verifier, VT_OWNERID) &&
					VerifyField<uint16_t>(verifier, VT_SRC_X) &&
					VerifyField<uint16_t>(verifier, VT_SRC_Y) &&
					VerifyField<uint16_t>(verifier, VT_DST_X) &&
					VerifyField<uint16_t>(verifier, VT_DST_Y) &&
					VerifyField<uint16_t>(verifier, VT_W) &&
					VerifyField<uint16_t>(verifier, VT_H) &&
					verifier.EndTable();
			}
		};

		struct bulletBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_id(uint16_t id) {
				fbb_.AddElement<uint16_t>(bullet::VT_ID, id, 0);
			}
			void add_ownerId(uint16_t ownerId) {
				fbb_.AddElement<uint16_t>(bullet::VT_OWNERID, ownerId, 0);
			}
			void add_src_x(uint16_t src_x) {
				fbb_.AddElement<uint16_t>(bullet::VT_SRC_X, src_x, 0);
			}
			void add_src_y(uint16_t src_y) {
				fbb_.AddElement<uint16_t>(bullet::VT_SRC_Y, src_y, 0);
			}
			void add_dst_x(uint16_t dst_x) {
				fbb_.AddElement<uint16_t>(bullet::VT_DST_X, dst_x, 0);
			}
			void add_dst_y(uint16_t dst_y) {
				fbb_.AddElement<uint16_t>(bullet::VT_DST_Y, dst_y, 0);
			}
			void add_w(uint16_t w) {
				fbb_.AddElement<uint16_t>(bullet::VT_W, w, 0);
			}
			void add_h(uint16_t h) {
				fbb_.AddElement<uint16_t>(bullet::VT_H, h, 0);
			}
			explicit bulletBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			bulletBuilder &operator=(const bulletBuilder &);
			flatbuffers::Offset<bullet> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<bullet>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<bullet> Createbullet(
			flatbuffers::FlatBufferBuilder &_fbb,
			uint16_t id = 0,
			uint16_t ownerId = 0,
			uint16_t src_x = 0,
			uint16_t src_y = 0,
			uint16_t dst_x = 0,
			uint16_t dst_y = 0,
			uint16_t w = 0,
			uint16_t h = 0) {
			bulletBuilder builder_(_fbb);
			builder_.add_h(h);
			builder_.add_w(w);
			builder_.add_dst_y(dst_y);
			builder_.add_dst_x(dst_x);
			builder_.add_src_y(src_y);
			builder_.add_src_x(src_x);
			builder_.add_ownerId(ownerId);
			builder_.add_id(id);
			return builder_.Finish();
		}

		struct deleteBullet FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_ID = 4,
				VT_OWNERID = 6
			};
			uint16_t id() const {
				return GetField<uint16_t>(VT_ID, 0);
			}
			uint16_t ownerId() const {
				return GetField<uint16_t>(VT_OWNERID, 0);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyField<uint16_t>(verifier, VT_ID) &&
					VerifyField<uint16_t>(verifier, VT_OWNERID) &&
					verifier.EndTable();
			}
		};

		struct deleteBulletBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_id(uint16_t id) {
				fbb_.AddElement<uint16_t>(deleteBullet::VT_ID, id, 0);
			}
			void add_ownerId(uint16_t ownerId) {
				fbb_.AddElement<uint16_t>(deleteBullet::VT_OWNERID, ownerId, 0);
			}
			explicit deleteBulletBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			deleteBulletBuilder &operator=(const deleteBulletBuilder &);
			flatbuffers::Offset<deleteBullet> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<deleteBullet>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<deleteBullet> CreatedeleteBullet(
			flatbuffers::FlatBufferBuilder &_fbb,
			uint16_t id = 0,
			uint16_t ownerId = 0) {
			deleteBulletBuilder builder_(_fbb);
			builder_.add_ownerId(ownerId);
			builder_.add_id(id);
			return builder_.Finish();
		}

		struct bullets FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
			enum {
				VT_VECBULLETS = 4
			};
			const flatbuffers::Vector<flatbuffers::Offset<bullet>> *vecBullets() const {
				return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<bullet>> *>(VT_VECBULLETS);
			}
			bool Verify(flatbuffers::Verifier &verifier) const {
				return VerifyTableStart(verifier) &&
					VerifyOffset(verifier, VT_VECBULLETS) &&
					verifier.Verify(vecBullets()) &&
					verifier.VerifyVectorOfTables(vecBullets()) &&
					verifier.EndTable();
			}
		};

		struct bulletsBuilder {
			flatbuffers::FlatBufferBuilder &fbb_;
			flatbuffers::uoffset_t start_;
			void add_vecBullets(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<bullet>>> vecBullets) {
				fbb_.AddOffset(bullets::VT_VECBULLETS, vecBullets);
			}
			explicit bulletsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
				: fbb_(_fbb) {
				start_ = fbb_.StartTable();
			}
			bulletsBuilder &operator=(const bulletsBuilder &);
			flatbuffers::Offset<bullets> Finish() {
				const auto end = fbb_.EndTable(start_);
				auto o = flatbuffers::Offset<bullets>(end);
				return o;
			}
		};

		inline flatbuffers::Offset<bullets> Createbullets(
			flatbuffers::FlatBufferBuilder &_fbb,
			flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<bullet>>> vecBullets = 0) {
			bulletsBuilder builder_(_fbb);
			builder_.add_vecBullets(vecBullets);
			return builder_.Finish();
		}

		inline flatbuffers::Offset<bullets> CreatebulletsDirect(
			flatbuffers::FlatBufferBuilder &_fbb,
			const std::vector<flatbuffers::Offset<bullet>> *vecBullets = nullptr) {
			return WarGame::fb::Createbullets(
				_fbb,
				vecBullets ? _fbb.CreateVector<flatbuffers::Offset<bullet>>(*vecBullets) : 0);
		}

		inline const WarGame::fb::playerBase *GetplayerBase(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::playerBase>(buf);
		}

		inline const WarGame::fb::players *Getplayers(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::players>(buf);
		}

		inline const WarGame::fb::requestId *GetrequestId(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::requestId>(buf);
		}

		inline const WarGame::fb::bullet *Getbullet(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::bullet>(buf);
		}

		inline const WarGame::fb::bullets *Getbullets(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::bullets>(buf);
		}

		inline const WarGame::fb::deleteBullet *GetdeleteBullet(const void *buf) {
			return flatbuffers::GetRoot<WarGame::fb::deleteBullet>(buf);
		}

		inline const char *playerBaseIdentifier() {
			return "PLAY";
		}

		inline const char *playersIdentifier() {
			return "VPLA";
		}

		inline const char *requestIdIdentifier() {
			return "RQID";
		}

		inline const char *bulletIdentifier() {
			return "BULL";
		}

		inline const char *bulletsIdentifier() {
			return "BULS";
		}

		inline const char *deleteBulletIdentifier() {
			return "DBUL";
		}

		inline bool playerBaseBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, playerBaseIdentifier());
		}

		inline bool playersBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, playersIdentifier());
		}

		inline bool requestIdBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, requestIdIdentifier());
		}

		inline bool bulletBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, bulletIdentifier());
		}

		inline bool bulletsBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, bulletsIdentifier());
		}

		inline bool deleteBulletBufferHasIdentifier(const void *buf) {
			return flatbuffers::BufferHasIdentifier(
				buf, deleteBulletIdentifier());
		}


		inline bool VerifyplayerBaseBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::playerBase>(playerBaseIdentifier());
		}

		inline bool VerifyplayersBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::players>(playersIdentifier());
		}

		inline bool VerifyrequestIdBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::requestId>(requestIdIdentifier());
		}

		inline bool VerifybulletBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::bullet>(bulletIdentifier());
		}

		inline bool VerifybulletsBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::bullets>(bulletsIdentifier());
		}

		inline bool VerifydeleteBulletBuffer(
			flatbuffers::Verifier &verifier) {
			return verifier.VerifyBuffer<WarGame::fb::deleteBullet>(deleteBulletIdentifier());
		}

		inline void FinishplayerBaseBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::playerBase> root) {
			fbb.Finish(root, playerBaseIdentifier());
		}

		inline void FinishplayersBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::players> root) {
			fbb.Finish(root, playersIdentifier());
		}

		inline void FinishrequestIdBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::requestId> root) {
			fbb.Finish(root, requestIdIdentifier());
		}

		inline void FinishbulletBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::bullet> root) {
			fbb.Finish(root, bulletIdentifier());
		}

		inline void FinishbulletsBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::bullets> root) {
			fbb.Finish(root, bulletsIdentifier());
		}

		inline void FinishdeleteBulletBuffer(
			flatbuffers::FlatBufferBuilder &fbb,
			flatbuffers::Offset<WarGame::fb::deleteBullet> root) {
			fbb.Finish(root, deleteBulletIdentifier());
		}

	}  // namespace fb
}  // namespace WarGame

#endif  // FLATBUFFERS_GENERATED_WARGAME_WARGAME_FB_H_

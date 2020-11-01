<template>
  <div class="group-box">
    <span class="group-box-title">{{ state.title }}</span>
    <slot></slot>
  </div>
</template>

<script lang="ts">
import { defineComponent, reactive, watch } from "vue";

interface Props {
  title?: string | null;
}

export default defineComponent({
  name: "group-box",
  props: {
    title: String
  },
  setup(props: Props) {
    const state = reactive({
      title: props.title
    });

    watch(
      () => props.title,
      (val) => (state.title = val)
    );

    return {
      state
    };
  }
});
</script>

<style scoped>
.group-box {
  border-radius: 8px;
  border: 1px solid var(--border-color-light);
  padding: 25px;
  position: relative;
}
.group-box-title {
  position: absolute;
  top: -12px;
  left: 20px;
  padding: 5px;
  background-color: white;
  color: #000000a6;
}
</style>
